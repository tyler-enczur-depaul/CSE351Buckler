#include "nrf_pwm.h"
#include "nrf_gpio.h"
#include "nrf.h"

#define PWM_INSTANCE    NRF_PWM0  // Use PWM0 instance
#define PWM_PIN1        23        // GPIO pin for PWM channel 1
#define PWM_PIN2        24        // GPIO pin for PWM channel 2
#define PWM_PIN3        25        // GPIO pin for PWM channel 3

#define PWM_FREQUENCY   1000      // PWM frequency in Hz
#define PWM_TOP_VALUE   16000     // PWM period (16000 ticks @ 16 MHz)

#define PWM_CH0_DUTY .01 * PWM_TOP_VALUE
#define PWM_CH1_DUTY .3 * PWM_TOP_VALUE 
#define PWM_CH2_DUTY .9 * PWM_TOP_VALUE
#define PWM_CH3_DUTY  1 * PWM_TOP_VALUE

uint16_t pwm_seq[4] = {PWM_CH0_DUTY, PWM_CH1_DUTY, PWM_CH2_DUTY, PWM_CH3_DUTY};

// Function to initialize PWM (to be implemented)
void pwm_init(void) {
    PWM_INSTANCE->PSEL.OUT[0] = PWM_PIN1; //LED 2
    PWM_INSTANCE->PSEL.OUT[1] = PWM_PIN2; //LED 1
    PWM_INSTANCE->PSEL.OUT[2] = PWM_PIN3; //LED 0
    PWM_INSTANCE->MODE = 0;
    PWM_INSTANCE->PRESCALER = 2;
    PWM_INSTANCE->COUNTERTOP = PWM_TOP_VALUE;
    PWM_INSTANCE->LOOP = 0;
    PWM_INSTANCE->DECODER = 2;
    PWM_INSTANCE->SEQ[0].PTR = pwm_seq;
    PWM_INSTANCE->SEQ[0].CNT = 4;
    PWM_INSTANCE->SEQ[0].REFRESH = 0;
    PWM_INSTANCE->SEQ[0].ENDDELAY = 0; 
    PWM_INSTANCE->ENABLE = 1;
    PWM_INSTANCE->TASKS_SEQSTART[0] = 1;

}

int main(void) {
    pwm_init();

    while (1) {
        // Infinite loop, PWM runs independently
    }
}
