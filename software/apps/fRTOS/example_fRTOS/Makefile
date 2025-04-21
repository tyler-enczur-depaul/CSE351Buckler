# nRF application makefile
PROJECT_NAME = $(shell basename "$(realpath ./)")

# Configurations
NRF_IC = nrf52832
SDK_VERSION = 15
SOFTDEVICE_MODEL = blank


# Path to FreeRTOSs

# Source and header files

APP_SOURCE_PATHS += .

# APP_SOURCES = $(notdir $(wildcard ./*.c))

APP_SOURCES = main.c



$(info $$APP_SOURCES is [${APP_SOURCES}])



#include $(FreeRTOS_BASE_DIR)

# Path to base of nRF52-base repo
NRF_BASE_DIR = ../../../nrf52x-base/

# Include board Makefile (if any)
include ../../../boards/buckler_revC/Board.mk

# Include main Makefile
include $(NRF_BASE_DIR)make/AppMakefile.mk


