#include "error_check_wrappers.h"
#include "nrf_drv_gpiote.h"
#include "led.h"
#include "board.h"
#include "app_timer.h"

static void default_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {}

void gpio_out_checkinit(nrf_drv_gpiote_pin_t pin, nrf_drv_gpiote_out_config_t const *p_config) {
	if(nrf_drv_gpiote_out_init(pin, p_config) != NRF_SUCCESS) { led_on(LED_DEBUG); }
}

void gpio_in_checkinit(nrf_drv_gpiote_pin_t pin, 
					   nrf_drv_gpiote_in_config_t const * p_config, 
					   nrf_drv_gpiote_evt_handler_t evt_handler) {

	nrf_drv_gpiote_evt_handler_t h = evt_handler == NULL ? default_handler : evt_handler;
	if(nrf_drv_gpiote_in_init(pin, p_config, h) != NRF_SUCCESS) { led_on(LED_DEBUG); }
}

void app_timer_create_checkinit(app_timer_id_t * p_timer_id, 
								app_timer_mode_t mode, 
								app_timer_timeout_handler_t timeout_handler) {
	if(app_timer_create(&p_timer_id, mode, timeout_handler) != NRF_SUCCESS) { led_on(LED_DEBUG); }

}