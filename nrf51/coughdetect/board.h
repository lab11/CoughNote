#pragma once

#define LEDR 18
#define LEDG 20
#define LEDB 19

#define LED_DEBUG LEDR


#define ADC7680_SCK_PIN 2
#define ADC7680_MISO_PIN 3
#define ADC7680_CS_PIN 4
#define ADC7680_MOSI_PIN 24 // Junk pin 
#define ADC7680_SPI_NUM 1

#define SD_DETECT_PIN 21
#define SD_NATIVE_MOSI_PIN 1
#define SD_MOSI_SEL_PIN 8
#define SD_NATIVE_SCK_PIN 9
#define SD_MISO_PIN 10
#define SD_CS_PIN 7 // Junk pin

#define COMP1_PIN 22
#define COMP2_PIN 23

#define RV3049_CS_PIN		28		

#define FRAM_HOLD_PIN		14
#define FRAM_CS_PIN			15
#define FRAM_WP_PIN			16

#define NUC_SPI_SCK_PIN     0     /**< SPI clock GPIO pin number. */
#define NUC_SPI_MOSI_PIN    30     /**< SPI Master Out Slave In GPIO pin number. */
#define NUC_SPI_MISO_PIN    29     /**< SPI Master In Slave Out GPIO pin number. */