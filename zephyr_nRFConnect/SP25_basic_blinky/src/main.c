/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   3000

#define buck0_led DT_NODELABEL(bucklerled0)

static const struct gpio_dt_spec bled_0 = GPIO_DT_SPEC_GET(buck0_led, gpios);

int main() {
  int ret;
  if (!gpio_is_ready_dt(&bled_0)) {
    printk("Error: device not found.  Aborting test.\n");
    return 1;
  }
  ret = gpio_pin_configure_dt(&bled_0, GPIO_OUTPUT_ACTIVE);
  
  while(1){
    ret = gpio_pin_toggle_dt(&bled_0);
    k_msleep(1000);
    
  }
  
  return 0;
}
