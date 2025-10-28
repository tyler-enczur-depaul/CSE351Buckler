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

void SWI1_EGU1_IRQHandler(void) {
    NRF_EGU1->EVENTS_TRIGGERED[0]=0;
    // rest of the code follows here
    printf("Software Interrupt Received\n");
    printf("Software Interrupt Running");
    for (int i = 0; i < 10; ++i) {
        printf(".");
        nrf_delay_ms(1000);
        printf("\nSoftware Interrupt Done!\n");
    }
}

// Step B: Write an IRQ Handler/ISR for the Interrupt
void GPIOTE_IRQHandler(void) {
    // Clear the Events register
    printf("Interrupt Received\n");
    NRF_GPIOTE->EVENTS_IN[0]=0;
    gpio_clear(25);
    nrf_delay_ms(1000);
    gpio_set(25);
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
    
    gpio_config(28, INPUT);
    gpio_config(25, OUTPUT);
    gpio_set(25);


    // Steps for Setting up Interrupt
    // 1. configure the interrupt
    NRF_GPIOTE->CONFIG[0] = 0x121C01;


    // 2. enable interrupt -- NRF_GPIOTE->...
    NRF_GPIOTE->INTENSET = 1;

    // 3. enable IRQ on NVIC  -- NVIC_EnableIRQ(...)
    NVIC_EnableIRQ(GPIOTE_IRQn);
    software_interrupt_init();

    NVIC_SetPriority(GPIOTE_IRQn, 0);
    NVIC_SetPriority(SWI1_EGU1_IRQn, 1);

    while (1) {
        // Main application loop
        //printf("Looping\n");
        software_interrupt_generate();
        //__WFI();
    }
}

