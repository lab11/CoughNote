#pragma once
#include "board.h"
#include <stdint.h>
#include "spi_master2.h"

#ifndef ADC7680_SCK_PIN
#define ADC7680_SCK_PIN 0
#endif

#ifndef ADC7680_MISO_PIN
#define ADC7680_MISO_PIN 29
#endif

#ifndef ADC7680_CS_PIN
#define ADC7680_CS_PIN 24
#endif

#ifndef ADC7680_SPI_NUM
#define ADC7680_SPI_NUM 0
#endif

void ad7680_init(SPIModuleNumber n, SPIConfig_t *s);
void ad7680_setup();
void ad7680_read_raw_sample(uint8_t *rx_buff);
uint16_t ad7680_read_sample();