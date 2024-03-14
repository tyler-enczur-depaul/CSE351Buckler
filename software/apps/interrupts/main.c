#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "buckler.h"

<<<<<<< Updated upstream
void SWI1_EGU1_IRQHandler(void) {
    NRF_EGU1->EVENTS_TRIGGERED[0] = 0;
}

// Step B: Write an IRQ Handler/ISR for the Interrupt
=======
>>>>>>> Stashed changes
void GPIOTE_IRQHandler(void) {
    if (NRF_GPIOTE->EVENTS_IN[0] == 1) {
        NRF_GPIOTE->EVENTS_IN[0] = 0; // Clear interrupt for BUTTON0

        // Toggle LED0 for BUTTON0
        nrf_gpio_pin_toggle(BUCKLER_LED0);

        // Add a delay to make sure the LED turns off
        nrf_delay_ms(500);
        nrf_gpio_pin_toggle(BUCKLER_LED0);

        printf("Button0 Pressed\n");
    }

    if (NRF_GPIOTE->EVENTS_IN[1] == 1) {
        NRF_GPIOTE->EVENTS_IN[1] = 0; // Clear interrupt for SWITCH0

        // Toggle LED1 for SWITCH0
        nrf_gpio_pin_toggle(BUCKLER_LED1);

        // Add a delay to make sure the LED turns off
        nrf_delay_ms(500);
        nrf_gpio_pin_toggle(BUCKLER_LED1);

        printf("Switch0 Pressed\n");
    }
}

int main(void) {
    // Initialize LED and BUTTON pins on the Buckler board
    nrf_gpio_cfg_output(BUCKLER_LED0);
    nrf_gpio_cfg_output(BUCKLER_LED1);
    nrf_gpio_cfg_input(BUCKLER_BUTTON0, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUCKLER_SWITCH0, NRF_GPIO_PIN_PULLUP);

    //Configure GPIOTE for BUTTON0 interrupt
    NRF_GPIOTE->CONFIG[0] = 0x01 | GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos |
                           BUCKLER_BUTTON0 << GPIOTE_CONFIG_PSEL_Pos |
                           GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos;

<<<<<<< Updated upstream
  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");
 
// Step A: Configuration 
  // 1. configure
  // 2. enable interrupt
  // 3. enable IRQ on NVIC 
=======
    //Configure GPIOTE for SWITCH0 interrupt
    NRF_GPIOTE->CONFIG[1] = GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos |
                           BUCKLER_SWITCH0 << GPIOTE_CONFIG_PSEL_Pos |
                           GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos;
       // Enable interrupts for BUTTON0 and SWITCH0 in the NVIC
    NVIC_EnableIRQ(GPIOTE_IRQn);
>>>>>>> Stashed changes

    //NRF_GPIOTE->CONFIG[0] = 0X21C01;
    
    uint32_t * ptr_INTSET = (uint32_t) (0x40006304);
    *ptr_INTSET = 0x03;


    while (1) {
        // Main application loop
    }
}

