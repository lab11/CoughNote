#include "CoughDetect_v3.h"
#include "nrf_gpio.h"
#include <stdint.h>
#include <stdbool.h>
#include "led.h"

uint32_t pin_list[29] = {
    NUC_FRAM_CS,
    NUC_FRAM_WP, 
    NUC_FRAM_HOLD,
    NUC_RV3049_CS,
    NUC_RV3049_INT,
    NUC_SPI_MISO_PIN,
    FRAM_CS,
    FRAM_MISO,
    FRAM_SPI_SEL,
    SD_CS,
    SD_MISO,
    SD_DETECT,
    SD_ENABLE,
    ADC_CS,
    ADC_MISO,
    COMP1,
    COMP2,
    LED0,
    LED1,
    LED2
};

uint32_t nuc_pin_list[21] = {
    17,21,22,23,24,29,30,0,1,7,8,9,10,11,12,13,2,3,4,5,6
};

static bool check_pin(uint32_t p) {
    for(uint8_t i=0; i < 29; i++) {
        if(p == pin_list[i]) { return true; }
    }
    return false;
}


void configure_platform_pins() {
    for(uint32_t i=0;i<32;i++) {
        if(!check_pin(i)) {
            nrf_gpio_cfg_output(i);
            nrf_gpio_pin_clear(i);
        }
    }
    // Configure nucleum SPI pins
    nrf_gpio_cfg_output(NUC_SPI_MOSI_PIN); 
    nrf_gpio_cfg_output(NUC_SPI_SCK_PIN);
    nrf_gpio_cfg_input(NUC_SPI_MISO_PIN, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_pin_clear(NUC_SPI_MOSI_PIN); 
    nrf_gpio_pin_clear(NUC_SPI_SCK_PIN);

    // Configure nucleum FRAM
    nrf_gpio_cfg_output(NUC_FRAM_CS);
    nrf_gpio_cfg_output(NUC_FRAM_HOLD);
    nrf_gpio_cfg_output(NUC_FRAM_WP);
    nrf_gpio_pin_set(NUC_FRAM_CS);
    nrf_gpio_pin_set(NUC_FRAM_HOLD);
    nrf_gpio_pin_set(NUC_FRAM_WP);
    nrf_gpio_cfg_input(NUC_RV3049_INT, NRF_GPIO_PIN_NOPULL);

    //configure rtc
    nrf_gpio_cfg_output(NUC_RV3049_CS);
    nrf_gpio_pin_clear(NUC_RV3049_CS); // The cs line for the rtc is reveresed for some reason

    // Configure LED pins
    led_init(LED0);
    led_init(LED1);
    led_init(LED2);
    // Configure ADC pins
    nrf_gpio_cfg_output(ADC_CS);
    nrf_gpio_cfg_input(ADC_MISO, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_output(ADC_SCK);
    nrf_gpio_cfg_output(ADC_SCK);
    nrf_gpio_pin_set(ADC_CS);

    // Congigure FRAM pins
    nrf_gpio_cfg_output(FRAM_CS);
    nrf_gpio_cfg_input(FRAM_MISO, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_output(FRAM_MOSI_2); 
    nrf_gpio_cfg_output(FRAM_SCK_2);
    nrf_gpio_cfg_output(FRAM_SPI_SEL);
    nrf_gpio_pin_set(FRAM_CS);
    nrf_gpio_pin_set(FRAM_MOSI_2);
    nrf_gpio_pin_set(FRAM_SCK_2);
    nrf_gpio_pin_set(FRAM_SPI_SEL);

    // Configure SD pins
    nrf_gpio_cfg_output(SD_CS);
    nrf_gpio_cfg_output(SD_ENABLE);
    nrf_gpio_cfg_input(SD_DETECT, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(SD_MISO, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_output(SD_SCK);
    nrf_gpio_cfg_output(SD_MOSI);
    
    nrf_gpio_pin_set(SD_CS);
    nrf_gpio_pin_set(SD_ENABLE);
    nrf_gpio_pin_clear(SD_SCK);
    nrf_gpio_pin_clear(SD_MOSI);

    // Configure comparator pins
    nrf_gpio_cfg_input(COMP1, NRF_GPIO_PIN_NOPULL);
    nrf_gpio_cfg_input(COMP2, NRF_GPIO_PIN_NOPULL);
}

void configure_fram_fram() {
    nrf_gpio_pin_set(FRAM_SPI_SEL);
}

void configure_fram_adc() {
    nrf_gpio_pin_clear(FRAM_SPI_SEL);
}