/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   3000

#define buck0_led DT_ALIAS(bucklerled0)
#define buck1_led DT_ALIAS(bucklerled1)
#define buck2_led DT_ALIAS(bucklerled2)

static const struct gpio_dt_spec bled_0 = GPIO_DT_SPEC_GET(buck0_led, gpios);
static const struct gpio_dt_spec bled_1 = GPIO_DT_SPEC_GET(buck1_led, gpios);
static const struct gpio_dt_spec bled_2 = GPIO_DT_SPEC_GET(buck2_led, gpios);

int main() {
  int ret;
  if (!gpio_is_ready_dt(&bled_0)) {
    printk("Error: device not found.  Aborting test.\n");
    return 1;
  }
  ret = gpio_pin_configure_dt(&bled_0, GPIO_OUTPUT_ACTIVE);
  if (!gpio_is_ready_dt(&bled_1)) {
    printk("Error: device not found.  Aborting test.\n");
    return 1;
  }
  ret = gpio_pin_configure_dt(&bled_1, GPIO_OUTPUT_ACTIVE);
  if (!gpio_is_ready_dt(&bled_2)) {
    printk("Error: device not found.  Aborting test.\n");
    return 1;
  }
  ret = gpio_pin_configure_dt(&bled_2, GPIO_OUTPUT_ACTIVE);
  while(1){
    ret = gpio_pin_toggle_dt(&bled_0);
    k_msleep(1000);
    ret = gpio_pin_toggle_dt(&bled_1);
    k_msleep(2000);
    ret = gpio_pin_toggle_dt(&bled_2);
    k_msleep(4000);
  }
  
  return 0;
}
