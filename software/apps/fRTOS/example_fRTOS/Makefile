# nRF application makefile
PROJECT_NAME = $(shell basename "$(realpath ./)")

# Configurations
NRF_IC = nrf52832
SDK_VERSION = 15
SOFTDEVICE_MODEL = blank


# Path to FreeRTOSs
FreeRTOS_BASE_DIR = ../../../FreeRTOS_nRF/
# Source and header files
APP_HEADER_PATHS += .
APP_HEADER_PATHS += $(FreeRTOS_BASE_DIR)source/include
APP_HEADER_PATHS += $(FreeRTOS_BASE_DIR)/portable/GCC/nrf52/

APP_SOURCE_PATHS += .
APP_SOURCE_PATHS += $(FreeRTOS_BASE_DIR)source
APP_SOURCE_PATHS += $(FreeRTOS_BASE_DIR)portable/GCC/nrf52/
APP_SOURCE_PATHS += $(FreeRTOS_BASE_DIR)source/portable/MemMang

# APP_SOURCES = $(notdir $(wildcard ./*.c))

APP_SOURCES = main.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)source/tasks.c
#APP_SOURCES += ./Source/supporting_functions.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)source/list.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)source/queue.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)source/timers.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)portable/GCC/nrf52/port.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)portable/GCC/nrf52/port_cmsis.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)portable/GCC/nrf52/port_cmsis_systick.c
APP_SOURCES += $(FreeRTOS_BASE_DIR)source/portable/MemMang/heap_4.c



$(info $$APP_SOURCES is [${APP_SOURCES}])



#include $(FreeRTOS_BASE_DIR)

# Path to base of nRF52-base repo
NRF_BASE_DIR = ../../../nrf52x-base/

# Include board Makefile (if any)
include ../../../boards/buckler_revC/Board.mk

# Include main Makefile
include $(NRF_BASE_DIR)make/AppMakefile.mk


