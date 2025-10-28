

//** Code: Hard Timers 
//** Author: Umer Huzaifa
//** Comments: Keeping a separate app for the hardware timers and counters


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "app_error.h"
#include "app_timer.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "buckler.h"

void timer_init(uint8_t duration){
    // fill in this function to initialize a timer of your choice
    uint32_t ticks = duration * 31250; 
    NRF_TIMER4->CC[0] = ticks;
    if (ticks < 65536) {
        NRF_TIMER4->BITMODE = 0;
    }
    else if (ticks < 16777216) {
        NRF_TIMER4->BITMODE = 2;
    }
    else {
        NRF_TIMER4->BITMODE = 3;
    }
    NRF_TIMER4->PRESCALER = 9;
    NRF_TIMER4->MODE = 0;
    NRF_TIMER4->TASKS_CLEAR = 1;
    NRF_TIMER4->TASKS_START = 1;
}

uint32_t read_timer(){
    // fill in this function for reading the timer value on calling this function
    NRF_TIMER4->TASKS_CAPTURE[1]=1;
    return (uint32_t) NRF_TIMER4->CC[1];
}



int main(void) {
    ret_code_t error_code = NRF_SUCCESS;

    // initialize RTT library
    error_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(error_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    printf("Board initialized!\n");

    // You can use the NRF GPIO library to test your timers
    nrf_gpio_pin_dir_set(BUCKLER_LED0, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(BUCKLER_LED1, NRF_GPIO_PIN_DIR_OUTPUT);
    nrf_gpio_pin_dir_set(BUCKLER_LED2, NRF_GPIO_PIN_DIR_OUTPUT);

    uint8_t duration = 3; // or a time of your choice. 
    timer_init(duration);


    //nrf_delay_ms(3000);


    // loop forever
    while (1) {
        printf("Timer 4 readings are: %lu\n", read_timer());
        printf("Seconds: %.1f\n", ((float)read_timer())/31250);
        nrf_delay_ms(50);
        if (NRF_TIMER4->EVENTS_COMPARE[0]) {
            NRF_TIMER4->TASKS_CLEAR = 1;
            NRF_TIMER4->EVENTS_COMPARE[0] = 0;
        }
        //printf("Timer 4 readings are: %d \n", read_timer());

    }
}
