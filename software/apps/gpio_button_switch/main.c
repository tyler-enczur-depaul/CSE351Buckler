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

    gpio_direction_t dir = INPUT;
    gpio_config(22, dir);
    gpio_config(28, dir);

    bool switch_state = false;
    bool button_state = false;
    // loop forever
    while (1) {
        if ((gpio_manage->IN & (1 << 22)) != switch_state) {
            switch_state = !switch_state;
            printf("Switch %s\n", switch_state ? "ON" : "OFF");
        }
        if ((gpio_manage->IN & (1 << 28)) != button_state) {
            button_state = !button_state;
            printf("button %s\n", button_state ? "ON" : "OFF");
        }
        nrf_delay_ms(10); // check every 10ms
    }
}
