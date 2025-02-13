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

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");

  //uint32_t* OUTSET = (uint32_t *)0x50000508;
  //uint32_t* OUTCLR = (uint32_t *)0x5000050c;
  //uint32_t* CNF_0 = (uint32_t *)0x50000700;





  // loop forever

  uint8_t ledNum = 0;

  gpio_config(23, 1);
  gpio_config(24, 1);
  gpio_config(25, 1);

  uint32_t delay = 100;
  int8_t direction = -1;




  //typedef struct {
  //  int age;
  //  float weight;
  //} TheStruct;
  //
  //TheStruct* ptr = (TheStruct*)0x20000000;
  //
  //ptr->age = 40;
  //ptr->weight = 285.5;







  gpio_config(28, 0);
  gpio_config(22, 0);

  while (1) {
    //printf("\nOUTSET: 0x%p", OUTSET);
    //printf("\nOUTCLR: 0x%p", OUTCLR);
    //printf("\nCNF_0: 0x%p", CNF_0);
    //printf("\n\n");


    //printf("\nbase struct (0x%p)", ptr);
    //printf("\nage field (0x%p): %d", &ptr->age, ptr->age);
    //printf("\nweight field (0x%p): %f", &ptr->weight, ptr->weight);
    //printf("\n\n");

    // printf("\n================================");
    // printf("\n28: %d", gpio_read(28));
    // printf("\n22: %d", gpio_read(22));
    // printf("\n================================");
    // printf("\n\n");

    gpio_read(28);
    gpio_read(22);
    nrf_delay_ms(delay);


//    if (ledNum == 0) {
//      //gpio_set(23);
//      gpio_set(24);
//      gpio_set(25);
//      gpio_clear(23);
//      //gpio_clear(24);
//      //gpio_clear(25);
//    } else if (ledNum == 1) {
//      gpio_set(23);
//      //gpio_set(24);
//      gpio_set(25);
//      //gpio_clear(23);
//      gpio_clear(24);
//      //gpio_clear(25);
//    } else if (ledNum == 2) {
//      gpio_set(23);
//      gpio_set(24);
//      //gpio_set(25);
//      //gpio_clear(23);
//      //gpio_clear(24);
//      gpio_clear(25);
//    } else {
//      gpio_set(23);
//      gpio_set(24);
//      gpio_set(25);
//    }
//
//    ledNum = (ledNum + 1) % 4;
//
//    nrf_delay_ms(delay);
//
//    delay += direction;
//
//    if (delay > 100) {
//      delay = 100;
//      direction = -1;
//    } else if (delay < 1) {
//      delay = 1;
//      direction = 1;
//    }



  }
}
