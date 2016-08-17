PROJECT_NAME = $(shell basename "$(realpath ./)")

# Modify these lines to define the search paths for source files
NRF_BASE_PATH ?= /home/wwhuang/Dropbox/git/nrf5x-base
LIBRARY_PATHS += . $(NRF_BASE_PATH)/devices ../components 
SOURCE_PATHS += $(NRF_BASE_PATH)/devices ../components 

# Define various metadata here
SOFTDEVICE_MODEL = s130
RAM_KB = 32
ENABLE_WIRELESS_DFU = 1
HW_REVISION = 0.0.1
FW_REVISION = 0.0.1
SDK_VERSION = 11

#Add c files here. Nothing needed for h files
APPLICATION_SRCS = $(notdir $(wildcard ./*.c))
APPLICATION_SRCS += softdevice_handler.c
APPLICATION_SRCS += ble_advdata.c
APPLICATION_SRCS += ble_conn_params.c
APPLICATION_SRCS += simple_ble.c
APPLICATION_SRCS += simple_adv.c

APPLICATION_SRCS += app_timer.c
APPLICATION_SRCS += app_error.c
APPLICATION_SRCS += led.c

APPLICATION_SRCS += nrf_drv_common.c
APPLICATION_SRCS += nrf_drv_gpiote.c
APPLICATION_SRCS += nrf_drv_spi.c

APPLICATION_SRCS += ad7680.c
APPLICATION_SRCS += spi_master2.c
APPLICATION_SRCS += sd_routines.c
APPLICATION_SRCS += rv3049.c

APPLICATION_SRCS += error_check_wrappers.c

#CENTRAL_LINK_COUNT = 4

include /home/wwhuang/Dropbox/git/CoughSense/nrf51/components/Makefile.RTC
include $(NRF_BASE_PATH)/make/Makefile
