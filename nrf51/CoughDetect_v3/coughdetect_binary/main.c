/*
    App to test the full functionality of CoughDetect
    1) app senses when we see enough 18 kHz noise (100 mV above Vref on Comp2)
    2) One second write from ADC to FRAM.
    3) Get timestamp
    4) Write data from FRAM to flash. Format is 4 bytes time, 4 bytes sample count, samples.
    5) Update CoughDetect advertisement to new time of last cough detected.

    This version works by recording once a certain threshold of 18 kHz noise is reached. There's no attempt to use
    the audio frontend to measure the length of the cough. Users will wear the sensor with the microphone facing inwards
    towards the lungs.

*/

#include <stdbool.h>
#include <stdint.h>

#include "led.h"
#include "nordic_common.h"
#include "softdevice_handler.h"
#include "nrf_soc.h"
#include "nrf.h"
#include "CoughDetect_v3.h"
#include "simple_timer.h"
#include "app_timer.h"
#include "simple_ble.h"
#include "simple_adv.h"
#include "spi_master2.h"
#include "fm25vn10.h"
#include "ad7680.h"
#include "nrf_drv_gpiote.h"
#include "nrf_soc.h"
#include "nrf_gpio.h"
#include "rv3049.h"
#include "simple_logger.h"
#include "chanfs/ff.h"
#include "diskio.h"
#include "nrf_delay.h"

#define UMICH_COMPANY_IDENTIFIER 0x02E0
#define DEVICE_NAME "CoughDet"
#define PHYSWEB URL "goo.gl/fill_in_something"
#define BLE_ADV_DATA_SIZE 9 // 1 id + 4 sample time + 4 cough count
#define DATA_LOG_SIZE 6000
#define M_COUGH_ID 1

typedef enum {
    START_SAMPLE,
    STOP_SAMPLE,
} app_status_types;

/* Global Variable declarations */
static uint8_t adc_buf[3]; // Junk buffer for ADC driver. In practice it's directly written to the FRAM
static uint32_t sample_counter = 0; // Count how many samples were taken in the second.
APP_TIMER_DEF(sample_timer); // used to time how long we sample for
const uint32_t sample_length = APP_TIMER_TICKS(1000, 0); // Sample time in ticks instead of ms
static app_status_types app_status = STOP_SAMPLE; // Status used in main loop to determine if we want to sample or sleep
nrf_drv_gpiote_in_config_t comp_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false);
static uint32_t cough_count = 0;

/* BLE metadata */
static uint8_t cough_adv_buf[BLE_ADV_DATA_SIZE] = {};
static ble_advdata_manuf_data_t mfgdata; // configuration data for BLE advertisements
static simple_ble_service_t cough_service = {
    .uuid128 = {{0x9c, 0x16, 0x35, 0x86, 0x30, 0x2b, 0x40, 0xb9, 0x89, 0x1f, 0x8a, 0x4c, 0x02, 0x19, 0x2c, 0xc5}}
};
static simple_ble_char_t base_station_rdy_char = {.uuid16 = 0x0201};
static uint8_t base_station_rdy_buf = 0;
static simple_ble_char_t sys_time_char = {.uuid16 = 0x0202}; // character which we will use to reset our time
static uint32_t sys_time_buf = 0; // where we store the time the gateway tells us.
static simple_ble_config_t ble_config = {
    .platform_id       = 0xe0,              // used as 4th octect in device BLE address
    .device_id         = DEVICE_ID_DEFAULT,
    .adv_name          = DEVICE_NAME,
    .adv_interval      = MSEC_TO_UNITS(500, UNIT_0_625_MS),
    .min_conn_interval = MSEC_TO_UNITS(500, UNIT_1_25_MS),
    .max_conn_interval = MSEC_TO_UNITS(1000, UNIT_1_25_MS)
};

/* Stat Variables */
static bool ble_connected = false; 
static bool base_station_ready = false;

/* 
void ble_evt_connected(ble_evt_t* p_ble_evt) {
    ble_connected = true;
    configure_fram_fram(); 
}

void services_init() {
    simple_ble_add_service(&cough_service);
    simple_ble_add_characteristic(1, 1, 1, 0, // read, write, notify, vlen
                                  4, (uint8_t *) &sys_time_buf, &cough_service, &sys_time_char); // size, buffer, service, char
}

void ble_evt_write(ble_evt_t *p_ble_evt) {
    if(simple_ble_is_char_event(p_ble_evt, &base_station_rdy_char)) {
       base_station_ready = true;
    }
    else if(simple_ble_is_char_event(p_ble_evt, &sys_time_char)) {
        set_unixtime(sys_time_buf);        
    }
}

void ble_evt_disconnected(ble_evt_t *p_ble_evt) {
    ble_connected = false;
    base_station_ready = false;
    nrf_drv_gpiote_in_event_enable(COMP2, true);
}
*/ 

void comp1_handler(void *p_context) {
    nrf_drv_gpiote_in_event_disable(COMP1);
    if(!ble_connected) {
        app_status = START_SAMPLE;
        cough_count++;
        led_on(LED_BLUE);
    }
}

void comp2_handler(void *p_context) {
    nrf_drv_gpiote_in_event_disable(COMP2);
        if(!ble_connected) {
        app_status = START_SAMPLE;
        cough_count++;
        led_on(LED_BLUE);
    }
}

void sample_timer_handler(void *p_context) {
    app_status = STOP_SAMPLE;
}


static volatile uint8_t checker = 0;
void junk_func1() {
    checker += 2;
}

int main(void) {
    // Configure pins and sleep level, init RTC
    configure_platform_pins();
    if(!nrf_drv_gpiote_is_init()) {nrf_drv_gpiote_init();}
    rv3049_init(SPI0, &nuc_rtc_spi, NUC_RV3049_CS);

    // Setup BLE advertisements
    cough_adv_buf[0] = (uint8_t) M_COUGH_ID;
    mfgdata.company_identifier = UMICH_COMPANY_IDENTIFIER;
    mfgdata.data.size = BLE_ADV_DATA_SIZE;
    mfgdata.data.p_data = cough_adv_buf;
    simple_ble_init(&ble_config);
    simple_adv_manuf_data(&mfgdata);

    // Init fram and adc
    configure_fram_fram();
    fram_init(SPI0, &fram_spi, FRAM_CS);
    fram_sleep();
    ad7680_init(SPI0, &adc_spi);
    /* Initialize the SDCard with a data file, then shut off */
    if(simple_logger_init("cc.bin", "a") != 0) {
        simple_logger_debug_stopper();
    };
    if(simple_logger_stop() != 0) {
        simple_logger_debug_stopper();
    }

    // Setup timers and comparator trigger
    app_timer_create(&sample_timer, APP_TIMER_MODE_SINGLE_SHOT, sample_timer_handler);
    nrf_drv_gpiote_in_init(COMP2, &comp_config, comp2_handler);
    nrf_drv_gpiote_in_event_enable(COMP2, true);
    //nrf_drv_gpiote_in_init(COMP1, &comp_config, comp1_handler);
    //nrf_drv_gpiote_in_event_enable(COMP1, true);
    while (1) {
        if(app_status == START_SAMPLE) {
            /* Sample to FRAM for a second */
            fram_init(SPI0, &fram_spi, FRAM_CS);
            configure_fram_fram();
            fram_prepare_write(0);
            ad7680_init(SPI0, &adc_spi);
            configure_fram_adc();
            app_timer_start(sample_timer, sample_length, NULL);
            while(app_status == START_SAMPLE) {
                ad7680_read_raw_sample(adc_buf);
                sample_counter++;
            }
            configure_fram_fram();
            fram_done_write();
            /* Get RTC sample time. Technically a little delayed, but shouldn't matter */
            uint32_t utime = get_unixtime(); 
            /* Update BLE Advertisement */
            for(uint8_t i = 0; i < 4; i++) {
                cough_adv_buf[i+1] = utime >> 8 * (3-i);
                cough_adv_buf[i+5] = cough_count >> 8 * (3-i);
            }
            simple_adv_manuf_data(&mfgdata);
            led_on(LED_RED);
            /* Write data from FRAM to ADC */
            simple_logger_start();
            simple_logger_fast_log_binary((void *)&utime, 4);
            simple_logger_fast_log_binary((void *)&sample_counter, 4);
            uint8_t data_buf[600];
            uint32_t position = 0; // our current position in the
            configure_fram_fram();
            fram_init(SPI0, &fram_spi, FRAM_CS);
            while(sample_counter > 200) {
                fram_read(position, 600, data_buf);
                for(uint32_t i=0; i < 600; i+=3) {
                    // strip leading and trailing zeroes from each reading
                    uint16_t true_sample = 0;
                    true_sample += data_buf[i];
                    true_sample <<= 8;
                    true_sample += data_buf[i+1];
                    true_sample <<= 4;
                    true_sample += data_buf[i+2] >> 4;
                    simple_logger_fast_log_binary((void *)&true_sample, 2);
                }
                sample_counter -= 200;
                position += 600;
            }
            fram_read(position, sample_counter * 3, data_buf);
            junk_func1();
            for(uint32_t j=0; j < sample_counter; j+= 3) {
                // strip leading and trailing zeroes from each reading
                uint32_t true_sample = 0;
                true_sample += data_buf[j];
                true_sample <<= 8;
                true_sample += data_buf[j+1];
                true_sample <<= 4;
                true_sample += data_buf[j+2] >> 4;
                simple_logger_fast_log_binary((void *)true_sample, 2);
            }
            led_off(LED_RED);
            simple_logger_stop();
            led_off(LED_BLUE);
            /* Reset sample counter and re-enable gpio interrupt*/
            sample_counter = 0;
            nrf_drv_gpiote_in_event_enable(COMP2, true);
            //nrf_drv_gpiote_in_event_enable(COMP1, true);
        }
        if(ble_connected && base_station_ready) {
            sys_time_buf = get_unixtime();
            simple_ble_notify_char(&sys_time_char);
        }
        sd_power_mode_set(NRF_POWER_MODE_LOWPWR);
        sd_app_evt_wait();
    }
}
