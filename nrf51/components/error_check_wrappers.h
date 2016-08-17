/* Wrapped functions which check errors and light up an led for you */

#pragma once
#include "nrf_drv_gpiote.h"
#include "app_timer.h"

void gpio_out_checkinit(nrf_drv_gpiote_pin_t pin, nrf_drv_gpiote_out_config_t const *p_config);
void gpio_in_checkinit(nrf_drv_gpiote_pin_t pin, 
					   nrf_drv_gpiote_in_config_t const * p_config, 
					   nrf_drv_gpiote_evt_handler_t evt_handler);
void app_timer_create_checkinit(app_timer_id_t * p_timer_id, 
								app_timer_mode_t mode, 
								app_timer_timeout_handler_t timeout_handler);