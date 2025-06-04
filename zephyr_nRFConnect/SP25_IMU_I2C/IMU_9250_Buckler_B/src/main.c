/*
 * Zephyr application for reading ambient light from OPT3004 sensor via I2C
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>

/* Locate and place these header files in the src folder*/
#include "mpu9250.h"

lsm9ds1_measurement_t lsm9ds1_read_accelerometer() {
  lsm9ds1_measurement_t meas = {0};
  uint8_t temp[6];

  // TODO: Use i2c_burst_read_dt or individual byte reads to get OUT_X_L_XL to OUT_Z_H_XL
  // IMPORTANT: When passing the register for reading operation
  // TODO: Combine bytes into int16_t ax, ay, az
  // TODO: Multiply each axis by aRes and store in meas

  return meas;
}

lsm9ds1_measurement_t lsm9ds1_read_gyro() {
  lsm9ds1_measurement_t meas = {0};
  uint8_t temp[6];

  // TODO: Use i2c_burst_read_dt or individual byte reads to get OUT_X_L_G to OUT_Z_H_G
  // TODO: Combine bytes into int16_t gx, gy, gz
  // TODO: Multiply each axis by gRes and store in meas

  return meas;
}

int main(void) {
  

	// 1. Configuration of I2C sensor for Accelerometer, Gyroscope,
	// 

	if (mpu9250_init()!=0){
		printk("Failed to configure the Sensor \n");
		return -1;
	}

	printk("Successfully configured the Sensor\n ");


	// lsm9ds1_measurement_t result;
	mpu9250_measurement_t result;
	while(1){
		// 2. Reading Operation from the sensor
		// result = lsm9ds1_read_accelerometer();
		result = mpu9250_read_accelerometer();
		// printk("Reading from the sensor \n");
		// 3. Displaying the result
		printk("X Axis: %2.2f, Y Axis: %2.2f, Z Axis: %2.2f \n",
       (double)result.x_axis, (double)result.y_axis, (double)result.z_axis);

		k_msleep(100);
	}
	
}

