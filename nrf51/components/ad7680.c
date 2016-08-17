#include "board.h"
#include "ad7680.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "nrf_drv_spi.h"
#include "spi_master2.h"
#include <stdint.h>


static SPIConfig_t *spi_config;
static SPIModuleNumber spi_num;

void ad7680_init(SPIModuleNumber n, SPIConfig_t *s) {
	spi_config = s; 
	spi_num = n;
	spi_master_init(spi_num, spi_config);
}

void ad7680_setup() {
	spi_master_init(spi_num, spi_config);
}

uint16_t ad7680_read_sample() {
	return 0;
}

void ad7680_read_raw_sample(uint8_t *rx_buff) {
	spi_master_rx(spi_num, 3, rx_buff);
}
