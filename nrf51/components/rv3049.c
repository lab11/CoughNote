#include <time.h>

#include "rv3049.h"
#include "spi_master2.h"
#include "nrf_gpio.h"

// Check that the application was compiled with the RTC constants for
// initialization
#ifndef RTC_SECONDS
#error "To use the RTC you must compile with RTC_ initial values."
#endif

static SPIConfig_t *spi_config;
static SPIModuleNumber spi_num;
static uint32_t cs_pin;

uint8_t rv3049_binary_to_bcd (uint8_t binary) {
  uint8_t out = 0;

  if (binary >= 40) {
    out |= 0x40;
    binary -= 40;
  }
  if (binary >= 20) {
    out |= 0x20;
    binary -= 20;
  }
  if (binary >= 10) {
    out |= 0x10;
    binary -= 10;
  }
  out |= binary;
  return out;
}

static void clr_cs_pin() {nrf_gpio_pin_clear(cs_pin);}
static void set_cs_pin() {nrf_gpio_pin_set(cs_pin);}

void rv3049_write_reg(uint8_t addr, uint8_t reg) {
    uint8_t cmd = RV3049_SET_WRITE_BIT(addr);
    uint8_t buf[2] = {cmd, reg};
    set_cs_pin();
    spi_master_tx(spi_num, 2, buf);
    clr_cs_pin();
}

uint8_t rv3049_read_reg(uint8_t addr) {
    uint8_t cmd = RV3049_SET_READ_BIT(addr);
    uint8_t buf;
    set_cs_pin();
    spi_master_tx(spi_num, 1, &cmd);
    spi_master_rx(spi_num, 1, &buf);
    clr_cs_pin();
    return buf;
}

void rv3049_init(SPIModuleNumber n, SPIConfig_t *s, uint32_t p) {
  spi_num = n;
  spi_config = s;
  spi_master_init(spi_num, spi_config);
  cs_pin = p;
  nrf_gpio_cfg_output(cs_pin);
  nrf_gpio_pin_clear(cs_pin);

  // Make sure PON bit is cleared, otherwise the RTC won't start counting
  uint8_t ctrl_reg = rv3049_read_reg(RV3049_PAGE_ADDR_CTRL_STATUS);
  if(ctrl_reg & 0x20) {
      rv3049_write_reg(RV3049_PAGE_ADDR_CTRL_STATUS, ctrl_reg & 0xDF);
  }

  // Write the initial values
  rv3049_time_t start_time = {RTC_SECONDS, RTC_MINUTES, RTC_HOURS,
                              RTC_DAYS, RTC_WEEKDAY, RTC_MONTH,
                              RTC_YEAR};
  rv3049_set_time(&start_time);
}

void rv3049_setup() {
  spi_master_init(spi_num, spi_config);
}

void rv3049_read_time(rv3049_time_t* time) {
  uint8_t buf[9];
  uint8_t addr = RV3049_SET_READ_BIT(RV3049_PAGE_ADDR_CLOCK_SEC);

  nrf_gpio_pin_set(cs_pin);
  spi_master_tx(spi_num, 1, &addr);
  spi_master_rx(spi_num, 7, buf);
  nrf_gpio_pin_clear(cs_pin);

  // Convert the values
  time->seconds = BCD_TO_BINARY(buf[0]);
  time->minutes = BCD_TO_BINARY(buf[1]);
  time->hours   = BCD_TO_BINARY((buf[2])&0x3F);
  time->days    = BCD_TO_BINARY(buf[3]);
  time->weekday = buf[4];
  time->month   = buf[5];
  time->year    = BCD_TO_BINARY(buf[6])+2000;
}

void set_unixtime(uint32_t t) {
  time_t tt = t;
  struct tm *raw = gmtime(&tt);
  uint8_t tbuf[8];
  tbuf[0] = 0; // subsecond
  tbuf[1] = (uint8_t) (raw->tm_sec);
  tbuf[2] = (uint8_t) (raw->tm_min);
  tbuf[3] = (uint8_t) (raw->tm_hour);
  tbuf[4] = 1; // pretend it's monday
  tbuf[5] = (uint8_t) (raw->tm_mday);
  tbuf[6] = (uint8_t) (raw->tm_mon + 1);
  uint16_t raw_year = (uint8_t) (raw->tm_year); // this is years since 1900
  rv3049_time_t t_new = {tbuf[1], tbuf[2], tbuf[3],
                         tbuf[5], 1, tbuf[6], raw_year + 1900}; 
  rv3049_setup();
  rv3049_set_time(&t_new);
}

uint32_t get_unixtime() {
  struct tm time_converter;
  rv3049_setup();
  rv3049_time_t raw_time;
  rv3049_read_time(&raw_time);
  time_converter.tm_year = raw_time.year - 1900;
  time_converter.tm_mon = raw_time.month - 1;
  time_converter.tm_mday = raw_time.days;
  time_converter.tm_hour = raw_time.hours;
  time_converter.tm_min = raw_time.minutes;
  return mktime(&time_converter); 
}

void rv3049_set_time(rv3049_time_t* time) {
  uint8_t buf[9];

  buf[0] = RV3049_SET_WRITE_BIT(RV3049_PAGE_ADDR_CLOCK_SEC);
  buf[1] = rv3049_binary_to_bcd(time->seconds);
  buf[2] = rv3049_binary_to_bcd(time->minutes);
  buf[3] = rv3049_binary_to_bcd(time->hours); // 24 hour mode
  buf[4] = rv3049_binary_to_bcd(time->days);
  buf[5] = time->weekday;
  buf[6] = time->month;
  buf[7] = rv3049_binary_to_bcd(time->year - 2000);

  nrf_gpio_pin_set(cs_pin);
  spi_master_tx(spi_num, 8, buf);
  nrf_gpio_pin_clear(cs_pin);
}
