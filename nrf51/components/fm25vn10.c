#include "fm25vn10.h"
#include "spi_master2.h"
#include <stdbool.h>
#include "nrf_gpio.h"

static const uint32_t max_size = 125000;
static const uint32_t max_addr = 0x1FFFF;
static SPIConfig_t *spi_config;
static SPIModuleNumber spi_num;
static uint32_t cs_pin;

static bool check_args(uint32_t addr, uint32_t size) {
    if(addr > max_addr || size > max_size) {return false;}
    return true;
}

static void cs_clr() {nrf_gpio_pin_clear(cs_pin);}
static void cs_set() {nrf_gpio_pin_set(cs_pin);}

void fram_init(SPIModuleNumber n, SPIConfig_t *s, uint32_t p) {
    spi_num = n;
    spi_config = s;
    spi_master_init(spi_num, spi_config);
    cs_pin = p;
    nrf_gpio_cfg_output(cs_pin);
    cs_set();
}

void fram_setup() {
    spi_master_init(spi_num, spi_config);
}

uint8_t fram_prepare_write(uint32_t addr) {
    if(!check_args(addr, 0)) {return FRAM_INVALID_ARGS;}
    uint8_t arg = FRAM_WREN;
    uint8_t cmd[4] = {FRAM_WRITE, addr >> 16, addr >> 8, addr};
    cs_clr();
    spi_master_tx(spi_num, 1, &arg);
    cs_set();
    cs_clr();
    spi_master_tx(spi_num, 4, cmd);
    return FRAM_SUCCESS;
}

void fram_done_write() {
    cs_set();
}
uint8_t fram_read(uint32_t addr, uint32_t size, uint8_t *buff) {
    if(!check_args(addr, size)) {return FRAM_INVALID_ARGS;}
    cs_clr();
    uint8_t cmd[4] = {FRAM_READ, addr >> 16, addr >> 8, addr};
    spi_master_tx(spi_num, 4, cmd);
    spi_master_rx(spi_num, size, buff);
    cs_set();
    return FRAM_SUCCESS;
}

uint8_t fram_write(uint32_t addr, uint32_t size, uint8_t *buff) {
    if(!check_args(addr, size)) {return FRAM_INVALID_ARGS;}
    fram_prepare_write(addr);
    spi_master_tx(spi_num, size, buff);
    fram_done_write();
    return FRAM_SUCCESS;
}

void fram_sleep() {
    uint8_t cmd = FRAM_SLEEP;
    cs_clr(); 
    spi_master_tx(spi_num, 1, &cmd);
    cs_set();
}