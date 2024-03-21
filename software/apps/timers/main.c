

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

void timer_init(uint8_t duration){
    // fill in this function to initialize a timer of your choice



}

uint32_t read_timer(){

    // fill in this function for reading the timer value on calling this function
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
      

    // placing a check for EVENTS_COMPARE[0]. This will be HIGH as soon as the desired time is reached.
    // Dont forget to set up the corresponding CC[0] for the value corresponding to duration . 
    while(NRF_TIMER4->EVENTS_COMPARE[0]){
      printf("%d seconds reached. \n", duration);
      // EVENTS_COMPARE[0] needs to be cleared for allowing it to run again.
      // for better readability on the terminal window, adding some delay is useful
      nrf_delay_ms(500);
    }

  }
}