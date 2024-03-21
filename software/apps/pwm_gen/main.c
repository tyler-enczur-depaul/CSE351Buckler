
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "app_error.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_pwm.h"

// Create the instance "PWM1" using TIMER1.

 

int main(void)
{
    ret_code_t err_code;

    /* 2-channel PWM, 200Hz, output on Buckler LED pins. */
    

    /* Switch the polarity of the second channel. */
    

    /* Initialize PWM. */
    err_code = ...
    APP_ERROR_CHECK(err_code);
    /* Enable PWM. */

    uint32_t value;
    while (true)
    {
        /* Your code for modifying the duty cycle value */
            
            // for catching any errors returned
            APP_ERROR_CHECK(...);
            nrf_delay_ms(25);
        
    }

}
