

//** Code: Hard Timers (Lab 6)
//** Author: Umer Huzaifa
//** Comments: 
//** Implementing a timer and a counter. 
//** Counter is another timer that can be triggered as we like instead of the clock signals


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

#include "gpio.h"

#include "buckler.h"

#define count_threshold 10000000


void timer_init(uint8_t duration){
    // all the register settings for setting up TIMER4 for 3 seconds timing operation

    uint32_t ticks = 93750; 
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
    NRF_TIMER4->INTENSET = 1 << 16;
    // Additional settings for declaring TIMER4 as an interrupt 

}

void counter_init(){
    // can be 16 bits in this case
    NRF_TIMER3->BITMODE = 0;
    NRF_TIMER3->MODE = 1;
    NRF_TIMER3->TASKS_CLEAR = 1;
    NRF_TIMER3->TASKS_START = 1;
}

uint32_t read_timer(){
    NRF_TIMER4->TASKS_CAPTURE[1]=1;
    return (uint32_t) NRF_TIMER4->CC[1];
}

uint32_t read_counter(){
    // just like TIMER4, read the values of TIMER3
    NRF_TIMER3->TASKS_CAPTURE[0]=1;
    return (uint32_t) NRF_TIMER3->CC[0];
}

// void GPIOTE_IRQHandler(void) {
//     // Clear the Events register
//     NRF_GPIOTE->EVENTS_IN[0]=0;
//     NRF_TIMER3->TASKS_COUNT = 1;
//     printf("Button Pressed! Count: %lu\n", read_counter());
// }

void TIMER4_IRQHandler(void) {
    uint32_t time = read_timer();
    printf("Timer 4 readings are: %ld which is %.1f seconds\n", time, (float)time/31250);
    printf("Counter readings are: %ld \n", read_counter());
    NRF_TIMER4->TASKS_CLEAR = 1;
    NRF_TIMER4->EVENTS_COMPARE[0] = 0; 
    NRF_TIMER3->TASKS_COUNT = 1;

}

int main(void) {
    ret_code_t error_code = NRF_SUCCESS;

    // initialize RTT library
    error_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(error_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    printf("Board initialized!\n");

    // You can use the NRF GPIO library to test your timers


    // gpio_config(28, INPUT);
    // NRF_GPIOTE->CONFIG[0] = 0x121C01;
    // NRF_GPIOTE->INTENSET = 1;
    NVIC_EnableIRQ(TIMER4_IRQn);
    NVIC_SetPriority(TIMER4_IRQn, 0);

    counter_init();
    timer_init(3);



    // loop forever
    while (1) {
        __WFE();

        // if (NRF_TIMER4->EVENTS_COMPARE[0]) {
        //     NRF_TIMER4->TASKS_CLEAR = 1;
        //     NRF_TIMER4->EVENTS_COMPARE[0] = 0;
        //     NRF_TIMER3->TASKS_COUNT = 1;
        // }
        

        // nrf_delay_ms(10);
    }
}

