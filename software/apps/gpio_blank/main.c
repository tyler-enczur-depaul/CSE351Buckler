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

  // Procedure to setup output

  
  int ans; 
  ans = 0x50000000 + 0x508;
  volatile unsigned int* GPIO_OUTSET = ans;
  printf("OUTSET at %p\n", GPIO_OUTSET);
  ans = 0x50000000 + 0x50C;
  volatile unsigned int* GPIO_OUTCLR = ans;
  printf("OUTCLR at %p\n", GPIO_OUTCLR);
  ans = 0x50000000 + 0x700;
  volatile unsigned int* GPIO_CNF0 = ans;
  printf("CNF0 at %p\n", GPIO_CNF0);

  int base = 0x50000000;
  int pin23 = base + 0x75C;
  int pin24 = base + 0x760;
  int pin25 = base + 0x764;

  uint32_t *pin23p = (uint32_t *) pin23;
  uint32_t *pin24p = (uint32_t *) pin24;
  uint32_t *pin25p = (uint32_t *) pin25;

  *pin23p = 1;
  *pin24p = 1;
  *pin25p = 1;

  //*GPIO_OUTCLR = 1<<23;
  *pin23p = 1;

  uint32_t pattern[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0};

  // button and switch code
  uint32_t pin28 = base + 0x778;
  uint32_t switch0 = base + 0x74C;

  uint32_t *pin28p = (uint32_t *)pin28;
  uint32_t *switch0p = (uint32_t *)switch0;

  *pin28p = 0;
  *switch0p = 0;
  	
  // loop forever
  while (1) {
    for (int i = 0; i < sizeof(pattern) / sizeof(pattern[0]); i += 3)
      {
        *pin23p= pattern[i];
        *pin24p= pattern[i + 1];
        *pin25p, pattern[i + 2];

        printf("BUTTON: %d, SWITCH0: %d\n", *pin28p, *switch0p);

        nrf_delay_ms(2000);
      }
  }
}

