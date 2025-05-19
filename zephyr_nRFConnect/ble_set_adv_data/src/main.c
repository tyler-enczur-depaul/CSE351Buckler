/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
/* Include the header file of the Bluetooth LE stack */

#include <dk_buttons_and_leds.h>

LOG_MODULE_REGISTER(Set_Adv, LOG_LEVEL_INF);

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define RUN_STATUS_LED DK_LED1
#define RUN_LED_BLINK_INTERVAL 1000

/* Declare the advertising packet */

/* Declare the URL data to include in the scan response */

/* Declare the scan response packet */

int main(void)
{
	int blink_status = 0;
	int err;

	LOG_INF("Starting Advertisement - 1 \n");

	err = dk_leds_init();
	if (err) {
		LOG_ERR("LEDs init failed (err %d)\n", err);
		return -1;
	}
	/* Enable the Bluetooth LE stack */

	/* Start advertising */

	LOG_INF("Advertising successfully started\n");

	for (;;) {
		dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
		k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
	}
}
