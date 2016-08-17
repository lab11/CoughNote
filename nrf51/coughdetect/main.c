#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "ad7680.h"
#include "led.h"
#include "nordic_common.h"
#include "softdevice_handler.h"
#include "spi_master2.h"
#include "nrf_drv_gpiote.h"
#include "simple_ble.h"
#include "simple_adv.h"
#include "nrf_soc.h"
#include "error_check_wrappers.h"
#include "app_timer.h"
#include "rv3049.h"
#include "nrf.h"

#define UMICH_COMPANY_IDENTIFIER 0x02E0
#define DEVICE_NAME "CoughDet"
#define PHYSWEB URL "goo.gl/fill_in_something"
#define DATA_SIZE 10
#define DATA_LOG_SIZE 6000

static simple_ble_service_t cough_service = {
    .uuid128 = {{0x9c, 0x16, 0x35, 0x86, 0x30, 0x2b, 0x40, 0xb9, 0x89, 0x1f, 0x8a, 0x4c, 0x02, 0x19, 0x2c, 0xc5}}
}; 
static simple_ble_char_t cough_char = {.uuid16 = 0x0201};
static simple_ble_char_t cough_char_ack = {.uuid16 = 0x0202};
static simple_ble_char_t cough_char_end = {.uuid16 = 0x0203}; 
static uint8_t cough_char_buf[DATA_SIZE] = {};
static uint8_t cough_char_ack_buf = 0;
static uint8_t cough_char_end_buf = 0;
static ble_advdata_manuf_data_t mandata;
static uint8_t cough_adv_buf[DATA_SIZE] = {};
APP_TIMER_DEF(pulse_timer);

static simple_ble_config_t ble_config = {
    .platform_id       = 0xe0,              // used as 4th octect in device BLE address
    .device_id         = DEVICE_ID_DEFAULT,
    .adv_name          = DEVICE_NAME,
    .adv_interval      = MSEC_TO_UNITS(500, UNIT_0_625_MS),
    .min_conn_interval = MSEC_TO_UNITS(500, UNIT_1_25_MS),
    .max_conn_interval = MSEC_TO_UNITS(1000, UNIT_1_25_MS)
}; 

static SPIConfig_t adc_spi =  {
                                .Config.Fields.BitOrder = SPI_BITORDER_MSB_LSB,
                                .Config.Fields.Mode     = SPI_MODE3,
                                .Frequency              = SPI_FREQ_2MBPS,
                                .Pin_SCK                = ADC7680_SCK_PIN,
                                .Pin_MOSI               = ADC7680_MOSI_PIN,
                                .Pin_MISO               = ADC7680_MISO_PIN,
                                .Pin_CSN                = ADC7680_CS_PIN
                              };

static SPIConfig_t sd_spi =  {
                                .Config.Fields.BitOrder = SPI_BITORDER_MSB_LSB,
                                .Config.Fields.Mode     = SPI_MODE3,
                                .Frequency              = SPI_FREQ_2MBPS,
                                .Pin_SCK                = SD_NATIVE_SCK_PIN,
                                .Pin_MOSI               = SD_NATIVE_MOSI_PIN,
                                .Pin_MISO               = SD_MISO_PIN,
                                .Pin_CSN                = SD_CS_PIN
                              };

static SPIConfig_t rv3049_spi = {
                                .Config.Fields.BitOrder = SPI_BITORDER_LSB_MSB, 
                                .Config.Fields.Mode = SPI_MODE3, 
                                .Frequency = SPI_FREQ_1MBPS, 
                                .Pin_SCK = NUC_SPI_SCK_PIN, 
                                .Pin_MOSI = NUC_SPI_MOSI_PIN, 
                                .Pin_MISO = NUC_SPI_MISO_PIN, 
                                .Pin_CSN = 17 // Dummy pin

                            }; 

static uint8_t adc_buff[3] = {};
static uint32_t adc_looper = 0;
static nrf_drv_gpiote_in_config_t comp1 = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false);
static nrf_drv_gpiote_in_config_t comp2 = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false);
static nrf_drv_gpiote_out_config_t sd_mosi_sel = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_LOW);
static nrf_drv_gpiote_in_config_t sd_detect = GPIOTE_CONFIG_IN_SENSE_HITOLO(false);

static nrf_drv_gpiote_out_config_t adc_cs = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);

// Make sure that the external rtc and fram pins are set correclty.
static nrf_drv_gpiote_out_config_t rtc_cs = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);
static nrf_drv_gpiote_out_config_t fram_cs = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);
static nrf_drv_gpiote_out_config_t fram_hold = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);
static nrf_drv_gpiote_out_config_t fram_wp = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);
static nrf_drv_gpiote_out_config_t nuc_spi_mosi = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_LOW);
static nrf_drv_gpiote_out_config_t nuc_spi_sck = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);
static nrf_drv_gpiote_out_config_t tester = GPIOTE_CONFIG_OUT_SIMPLE(NRF_GPIOTE_INITIAL_VALUE_LOW);
static nrf_drv_gpiote_in_config_t  nuc_spi_miso = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false); 

//Time vals 
static bool pulse_times_set = false;
static uint32_t initial_pulse_time = 0;
static uint32_t end_pulse_time = 0;
static uint32_t pulse_timeout = APP_TIMER_TICKS(5, 0); 
static uint32_t pulse_filter_length_max = APP_TIMER_TICKS(305, 0);
static uint32_t pulse_filter_length_min = APP_TIMER_TICKS(85, 0);


static uint8_t  data_log[DATA_LOG_SIZE] = {}; //format is 6 bytes rv3049 time + 4 bytes pulse length
static uint16_t data_log_index = 0;
static uint16_t data_reader_index = 0;

static rv3049_time_t m_time; // buffer for real time where each cough event occurs

void services_init() {
    simple_ble_add_service(&cough_service);
    simple_ble_add_characteristic(1, 0, 1, 0, // read, write, notify, vlen
                                  DATA_SIZE, cough_char_buf, &cough_service, &cough_char); 
    
    simple_ble_add_characteristic(0, 1, 0, 0, 
                                  1, &cough_char_ack_buf, &cough_service, &cough_char_ack);
    simple_ble_add_characteristic(1,0,1,0, 
                                  1, &cough_char_end_buf, &cough_service, &cough_char_end); 
}

void ble_evt_write(ble_evt_t *p_ble_evt) {
    if(simple_ble_is_char_event(p_ble_evt, &cough_char_ack)) {
        if (data_reader_index <= data_log_index - DATA_SIZE) {
            data_reader_index += DATA_SIZE;
            for(uint8_t i = 0; i < DATA_SIZE; i++) {
                cough_char_buf[i] = data_log[data_reader_index + i];
            }
            simple_ble_notify_char(&cough_char);
        }
        else {
            simple_ble_notify_char(&cough_char_end); 
        }
    }
}

void ble_evt_connected(ble_evt_t* p_ble_evt) {
    for (uint8_t i = 0; i < DATA_SIZE; i ++) {
        cough_char_buf[i] = data_log[data_reader_index + i];
    }
    simple_ble_notify_char(&cough_char); 
}

void ble_evt_disconnected(ble_evt_t *p_ble_evt) {

}

static void comp1_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) { 
    uint32_t t = NRF_RTC0->COUNTER;
    app_timer_stop(pulse_timer);
    if(pulse_times_set) {
        end_pulse_time = t;
    } else {
        nrf_drv_gpiote_out_clear(24);
        initial_pulse_time = t;
        pulse_times_set = true;
    }
    app_timer_start(pulse_timer, pulse_timeout , NULL); 
}

static void comp2_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) { 

}

static void pulse_timer_handler(void* p_context) {
    uint32_t time_diff = end_pulse_time - initial_pulse_time;
    nrf_drv_gpiote_out_set(24);
    if(data_log_index <= (DATA_LOG_SIZE - DATA_SIZE)) {
        rv3049_read_time(&m_time);
        data_log[data_log_index++] = m_time.year >> 8;
        data_log[data_log_index++] = m_time.year;
        data_log[data_log_index++] = m_time.month;
        data_log[data_log_index++] = m_time.days;
        data_log[data_log_index++] = m_time.hours;
        data_log[data_log_index++] = m_time.minutes;
        for(uint8_t i = 0; i < 4; i++) {
            data_log[data_log_index++] = time_diff >> (i * 8);
        }
    }
    if(time_diff < pulse_filter_length_max && time_diff > pulse_filter_length_min) {
        //led_toggle(LEDB);
        //led_off(LEDR);
        // Update advertisement data
        cough_adv_buf[0] = m_time.year >> 8;
        cough_adv_buf[1] = m_time.year;
        cough_adv_buf[2] = m_time.month;
        cough_adv_buf[3] = m_time.days;
        cough_adv_buf[4] = m_time.hours;
        cough_adv_buf[5] = m_time.minutes;
        for(uint8_t i = 0; i < 4; i ++) {
            cough_adv_buf[5 + i] = time_diff >> (i * 8);
        }
        simple_adv_manuf_data(&mandata);
    }
    
    end_pulse_time = 0; 
    initial_pulse_time = 0;
    pulse_times_set = false;

}

static void sd_detect_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {}

int main(void) {

    // Initialize some LEDs.
    led_init(LEDR);
    led_init(LEDB);
    led_init(LEDG);

    // Initialize adc driver
    //ad7680_init(SPI1, &adc_spi);

    // Init 
    rv3049_init(SPI1, &rv3049_spi, RV3049_CS_PIN);

    // Initialize GPIO driver and pins
    if(!nrf_drv_gpiote_is_init()) { nrf_drv_gpiote_init(); }
    comp1.pull = NRF_GPIO_PIN_NOPULL;
    comp2.pull = NRF_GPIO_PIN_NOPULL;
    sd_detect.pull = NRF_GPIO_PIN_NOPULL;

    gpio_in_checkinit(COMP1_PIN, &comp1, comp1_handler);
    gpio_in_checkinit(COMP2_PIN, &comp2, comp2_handler);
    gpio_in_checkinit(SD_DETECT_PIN, &sd_detect, sd_detect_handler);
    gpio_out_checkinit(SD_MOSI_SEL_PIN, &sd_mosi_sel);

    gpio_out_checkinit(RV3049_CS_PIN, &rtc_cs);
    gpio_out_checkinit(FRAM_HOLD_PIN , &fram_hold);     
    gpio_out_checkinit(FRAM_CS_PIN , &fram_cs);     
    gpio_out_checkinit(FRAM_WP_PIN, &fram_wp);     
    gpio_out_checkinit(NUC_SPI_MOSI_PIN, &nuc_spi_mosi);       
    gpio_out_checkinit(NUC_SPI_SCK_PIN, &nuc_spi_sck);    
    gpio_in_checkinit(NUC_SPI_MISO_PIN, &nuc_spi_miso, NULL);

    gpio_out_checkinit(ADC7680_CS_PIN, &adc_cs);

    gpio_out_checkinit(24, &tester); // Tester pin

    // Keep an RTC running for timing purposes
    NRF_RTC0->PRESCALER = 0;
    NRF_RTC0->TASKS_START = 1;

    // Simple BLE Init
    simple_ble_init(&ble_config);
    mandata.company_identifier = UMICH_COMPANY_IDENTIFIER;
    mandata.data.size = DATA_SIZE;
    mandata.data.p_data = cough_adv_buf;
    simple_adv_manuf_data(&mandata);

    uint32_t err = app_timer_create(&pulse_timer, APP_TIMER_MODE_SINGLE_SHOT, pulse_timer_handler);
    if( err != NRF_SUCCESS) { led_on(LEDG); }
    
    // Enable comparator triggers from analog filters 
    nrf_drv_gpiote_in_event_enable(COMP1_PIN, true);
    //nrf_drv_gpiote_in_event_enable(COMP2_PIN, true);
    
    // Enter main loop.
    while (1) {
        /*for(adc_looper=0; adc_looper < 40000; adc_looper++) {
            ad7680_read_raw_sample(adc_buff);
        }*/
        //power_manage();
        sd_app_evt_wait();
    }
}
