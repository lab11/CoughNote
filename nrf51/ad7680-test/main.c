#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "ad7680.h"
#include "led.h"
#include "nordic_common.h"
#include "softdevice_handler.h"
#include "spi_master2.h"

static uint8_t tx_buff[2] = {1,2};

int main(void) {

    // Initialize some LEDs.
    led_init(LEDR);
    led_init(LEDB);
    led_init(LEDG);

    led_on(LEDR);
    ad7680_init();
    SPIConfig_t my_spi = {.Config.Fields.BitOrder = SPI_BITORDER_MSB_LSB,
                          .Config.Fields.Mode     = SPI_MODE3,
                          .Frequency              = SPI_FREQ_8MBPS,
                          .Pin_SCK                = 8,
                          .Pin_MOSI               = 9,
                          .Pin_MISO               = 22,
                          .Pin_CSN                = 10};
    spi_master_init(SPI1, &my_spi);

    led_on(LEDB);


    while(1) {
    	ad7680_read_sample();
        spi_master_tx(SPI1, 2, tx_buff); 
    }

    // Enter main loop.
    while (1) {
        //power_manage();
        // sd_app_evt_wait();
    }
}
