//** Code: Hard Timers (Lab 6)
//** Author: Umer Huzaifa
//** Date: 12/30/2021
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

uint32_t counter_timer3 = 0;

uint32_t last_timer_value = 0; // Declare the variable

void timer_init(uint8_t duration) {
    NRF_TIMER4->TASKS_STOP = 1;
    NRF_TIMER4->MODE = TIMER_MODE_MODE_Timer;

    // Calculate the required prescaler and compare value for a 3-second duration
    uint32_t timer_frequency = 32768;  // not too sure
    uint32_t prescaler = timer_frequency - 1;
    uint32_t compare_value = timer_frequency * duration - 1;

    NRF_TIMER4->PRESCALER = prescaler;
    NRF_TIMER4->CC[0] = compare_value;

    NRF_TIMER4->BITMODE = 0x03;

    NRF_TIMER4->INTENSET = (1 << TIMER_INTENSET_COMPARE0_Pos);

    NRF_TIMER4->TASKS_START = 1;

    NVIC_EnableIRQ(TIMER4_IRQn);
}

uint32_t read_timer() {
    NRF_TIMER4->TASKS_CAPTURE[0] = 1;
    uint32_t captured_value = NRF_TIMER4->CC[0];
    return captured_value;
}

void timer3_init() {
    NRF_TIMER3->TASKS_STOP = 1;
    NRF_TIMER3->MODE = TIMER_MODE_MODE_Counter;  // Set TIMER3 to Counter mode
    NRF_TIMER3->PRESCALER = 0;

    // Set the compare value for 3 seconds
    NRF_TIMER3->CC[0] = 3 * 32768 - 1;

    NRF_TIMER3->BITMODE = 0x03;

    NRF_TIMER3->INTENSET = (1 << TIMER_INTENSET_COMPARE0_Pos);

    NRF_TIMER3->TASKS_START = 1;

    NVIC_EnableIRQ(TIMER3_IRQn);
}

void gpio_init() {
    nrf_gpio_cfg_input(BUCKLER_BUTTON0, NRF_GPIO_PIN_PULLUP);
    NRF_GPIOTE->CONFIG[0] = 0x21C01;

    NVIC_EnableIRQ(GPIOTE_IRQn);
    uint32_t * ptr_INTENSET = (uint32_t) (0x40006304);
    *ptr_INTENSET  = 0x03;
}

void GPIOTE_IRQHandler(void) {
    if (NRF_GPIOTE->EVENTS_IN[0] == 1) {
        NRF_GPIOTE->EVENTS_IN[0] = 0; // Clear the event

        // Button pressed, increment counter
        counter_timer3++;
        printf("Button pressed! Counter incremented. New value: %u\n", counter_timer3);
    }
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

    nrf_delay_ms(3000);

    // loop forever
    while (1) {

        printf("Timer 4 readings are: %d \n", read_timer());
        printf("Counter value TIMER3: %u \n", counter_timer3); 

        // Check if 3 seconds have passed
        if (NRF_TIMER3->EVENTS_COMPARE[0] == 1) {
            NRF_TIMER3->EVENTS_COMPARE[0] = 0; 

            printf("3 seconds have passed!\n");
        }

        if (NRF_GPIOTE->EVENTS_IN[0] == 1) {
            NRF_GPIOTE->EVENTS_IN[0] = 0; // Clear the event

            // Button pressed, increment counter
            counter_timer3++;
            printf("Button pressed! Counter incremented. New value: %u\n", counter_timer3);
        }

        uint32_t current_timer_value = NRF_TIMER4->CC[0];

        // Check if a 3-second interval has elapsed
        if (current_timer_value - last_timer_value >= duration * 32768) {
            printf("%d seconds reached. \n", duration);
            last_timer_value = current_timer_value;
	    counter_timer3++;

            // Adding some delay for better readability
            nrf_delay_ms(500);

            // Reset the timer for the next interval
            NRF_TIMER4->TASKS_STOP = 1;
            NRF_TIMER4->TASKS_CLEAR = 1;
            NRF_TIMER4->TASKS_START = 1;
        }
    }
}
