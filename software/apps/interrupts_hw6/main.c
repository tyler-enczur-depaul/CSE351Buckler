#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "software_interrupt.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "buckler.h"
#include "gpio.h"


void GPIOTE_IRQHandler(void) {

    if (NRF_GPIOTE->EVENTS_IN[0]) {
        gpio_clear(25);
        nrf_delay_ms(20);
        gpio_set(25);
        printf("Button pressed\n");
        NRF_GPIOTE->EVENTS_IN[0] = 0;
    }

    if (NRF_GPIOTE->EVENTS_IN[1]) {
        gpio_clear(24);
        nrf_delay_ms(20);
        gpio_set(24);
        printf("Switch switched\n");
        NRF_GPIOTE->EVENTS_IN[1] = 0;
    }

}

int main(void) {

    ret_code_t error_code = NRF_SUCCESS;
    // initialize RTT library
    error_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(error_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    printf("Log initialized!\n");

    // Initialize LED and BUTTON pins on the Buckler board
    //............    
    
    gpio_config(22, INPUT);
    gpio_config(28, INPUT);
    gpio_config(24, OUTPUT);
    gpio_config(25, OUTPUT);
    gpio_set(24);
    gpio_set(25);


    // Steps for Setting up Interrupt
    // 1. configure the interrupt
    NRF_GPIOTE->CONFIG[0] = 0x121C01;
    NRF_GPIOTE->CONFIG[1] = 0x121601;


    // 2. enable interrupt -- NRF_GPIOTE->...
    NRF_GPIOTE->INTENSET = 0b11;

    // 3. enable IRQ on NVIC  -- NVIC_EnableIRQ(...)
    NVIC_EnableIRQ(GPIOTE_IRQn);


    while (1) {
        // Main application loop
        //printf("Looping\n");
        //__WFI();
        //nrf_delay_ms(10); // check every 10ms
    }
}

