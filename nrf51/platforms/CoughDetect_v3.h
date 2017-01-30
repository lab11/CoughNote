#pragma once

#include "spi_master2.h"

#define DUMMY_CS 24

// FRAM chip pins
#define FRAM_CS 12
#define FRAM_MISO    6
#define FRAM_MOSI_2  5
#define FRAM_SCK_2   4
#define FRAM_SPI_SEL 11

//SD Card pins
#define SD_DETECT    21
#define SD_ENABLE    17
#define SD_CS        10
#define SD_MISO      7
#define SD_MOSI      9
#define SD_SCK       8

// ADC pins
#define ADC_CS   3
#define ADC_MISO 2
#define ADC_SCK  13

// Cough pins
#define COMP1 22
#define COMP2 23

// LED pins
#define LED0          18 // red
#define LED1          19 // blue
#define LED2          20 // green
#define LED_RED       LED0
#define LED_BLUE      LED1
#define LED_GREEN     LED2
#define LED_DEBUG     LED1

/* NUCLEUM PINS copied from nucleum.h. Copied so that I could use FRAM for my #defines*/

// This pin is mapped to the FTDI chip to all the device to enter the
// bootloader mode.
#define BOOTLOADER_CTRL_PIN  13
#define BOOTLOADER_CTRL_PULL NRF_GPIO_PIN_PULLUP

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  12
#define CTS_PIN_NUMBER 0
#define RTS_PIN_NUMBER 0
#define HWFC           false

#define NUC_SPI_SCK_PIN     0     /**< SPI clock GPIO pin number. */
#define NUC_SPI_MOSI_PIN    30     /**< SPI Master Out Slave In GPIO pin number. */
#define NUC_SPI_MISO_PIN    29     /**< SPI Master In Slave Out GPIO pin number. */
#define NUC_RV3049_CS		28
#define NUC_RV3049_INT		25
#define NUC_FRAM_HOLD       14
#define NUC_FRAM_CS		    15
#define NUC_FRAM_WP		    16
#define NUC_XL1				46
#define NUC_XL2				45

/* Pins for SD Card */
#define SPI_SCK_PIN     8     /**< SPI clock GPIO pin number. */
#define SPI_MOSI_PIN    9     /**< SPI Master Out Slave In GPIO pin number. */
#define SPI_MISO_PIN    7     /**< SPI Master In Slave Out GPIO pin number. */
#define SPI_CS_PIN		10
#define SD_ENABLE_PIN	17		//power gates sd card
#define CD_PIN			21

/* Various spi configurations defined in CoughDetect_v3.c */
extern SPIConfig_t adc_spi;
extern SPIConfig_t fram_spi;
extern SPIConfig_t sdcard_spi;
extern SPIConfig_t nuc_rtc_spi;

/* This function doesn't initialize functions such as spi, just sets the output/input correctly*/
void configure_platform_pins();

/* Configure fram chip to be hooked up to the nucleum */
void configure_fram_fram();

/* Configure FRAM chip to be shorted to ADC for direct writes */
void configure_fram_adc();
