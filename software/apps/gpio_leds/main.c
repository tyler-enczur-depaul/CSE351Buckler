// Blink app
//
// Blinks the LEDs on Buckler

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

#include "buckler.h"
#include "gpio.h"

int main(void) {
    ret_code_t error_code = NRF_SUCCESS;
    gpio_manage_t* gpio_manage = (gpio_manage_t*) GPIO_ADDR;

    // initialize RTT library
    error_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(error_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    printf("Log initialized!\n");

    uint32_t* outset = (uint32_t*)&(gpio_manage->OUTSET);
    uint32_t* outclr = (uint32_t*)&(gpio_manage->OUTCLR);
    uint32_t* cnf    = gpio_manage->PIN_CNF;

    printf("OUTSET: %p\nOUTCLR: %p\nCNF[0]: %p\n", outset, outclr, cnf);

    gpio_direction_t dir = OUTPUT;
    gpio_config(23, dir);
    gpio_config(24, dir);
    gpio_config(25, dir);
    // loop forever
    while (1) {
        gpio_set(23);
        gpio_set(24);
        gpio_set(25);
        nrf_delay_ms(1000);
        gpio_clear(23);
        gpio_clear(24);
        gpio_clear(25);
        nrf_delay_ms(1000);
    }
}
