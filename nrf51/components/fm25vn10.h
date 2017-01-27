#pragma once
#include <stdint.h>
#include "spi_master2.h"


#define FRAM_SUCCESS 0
#define FRAM_INVALID_ARGS 1
#define FRAM_INVALID_ADDR 2
#define FRAM_INVALID_SIZE 3

#define FRAM_WREN  0x06
#define FRAM_WRDI  0x04
#define FRAM_RDSR  0x05
#define FRAM_WRSR  0x01
#define FRAM_READ  0x03
#define FRAM_FSTRD 0x0B
#define FRAM_WRITE 0x02
#define FRAM_SLEEP 0xB9
#define FRAM_RDID  0x9F
#define FRAM_SNR   0xC3
#define FRAM_WAKEUP 400 // given in us

void fram_init(SPIModuleNumber n, SPIConfig_t *s, uint32_t p);

/* These two are used together for the cough detect project */
uint8_t fram_prepare_write(uint32_t addr);
void fram_done_write();


uint8_t fram_read(uint32_t addr, uint32_t size, uint8_t *buff);
uint8_t fram_write(uint32_t addr, uint32_t size, uint8_t *buff);
void fram_sleep();