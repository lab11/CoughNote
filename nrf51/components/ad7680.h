#pragma once
#include "board.h"
#include <stdint.h>
#include "spi_master2.h"

void ad7680_init(SPIModuleNumber n, SPIConfig_t *s);
void ad7680_setup();
void ad7680_read_raw_sample(uint8_t *rx_buff);
void ad7680_sleep();
uint16_t ad7680_read_sample();
