/*
 * Zephyr application for reading ambient light from OPT3004 sensor via I2C
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>

/* Locate and place these header files in the src folder*/
#include "lsm9ds1_registers.h"
#include "lsm9ds1_types.h"

#define SENSOR_NODE DT_NODELABEL(mysensor)
const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(SENSOR_NODE);

// Define global resolution scaling variables
float aRes, gRes;

void calcgRes() {
  // TODO: Use settings.gyro.scale and set gRes accordingly
}

void calcaRes() {
  // TODO: Use settings.accel.scale and set aRes accordingly
}

/*
  **********************************************************************
  **********************************************************************
  Writing an n byte Value to a Register (0xAB) on an I2C Device:

    uint8_t config_bytes[n+1];
      config_bytes[0] = 0xAB; // the address of the register
      config_bytes[1] = ..;   // first byte of Value
      config_bytes[2] = ..;   // second byte of Value
      ...
      config_bytes[n] = ..;   // last byte of Value
    
    int ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes))
    ret = 0 means success
  **********************************************************************
  **********************************************************************
*/

int lsm9ds1_init() {
  // TODO: Set values in the settings struct for gyro and accelerometer  

  // TODO: Call calcgRes() and calcaRes()

  // TODO: Configure CTRL_REG1_G, CTRL_REG2_G, CTRL_REG3_G, etc. for gyro
  // TODO: Configure CTRL_REG5_XL, CTRL_REG6_XL, CTRL_REG7_XL for accelerometer

  return 0; // return error if init fails
}

/*
  **********************************************************************
  **********************************************************************
  Reading an n byte Value from a Register (0xAB) on LSM9DS1:

    uint8_t result[n];
    
    int ret = i2c_burst_read_dt(&dev_i2c, 0xAB | 0x80 , result, n);

    ret = 0 means success
  **********************************************************************
  **********************************************************************

   **********************************************************************
  **********************************************************************
  Reading an n byte Value from a Register (0xAB) on typical I2C devices:

    uint8_t result[n];
    
    int ret = i2c_burst_read_dt(&dev_i2c, 0xAB , result, n);

    ret = 0 means success
  **********************************************************************
  **********************************************************************
*/
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
  if (!device_is_ready(dev_i2c.bus)) {
    printk("I2C device not ready\n");
    return -1;
  }

  printk("LSM9DS1 initialization...\n");

  if (lsm9ds1_init() != 0) {
    printk("Sensor initialization failed\n");
    return -1;
  }

  printk("Sensor initialized successfully\n");

  lsm9ds1_measurement_t result_a, result_g;

  while (1) {
    // TODO: Call lsm9ds1_read_accelerometer and lsm9ds1_read_gyro
    // TODO: Print results in one line: Accel -> X, Y, Z | Gyro -> X, Y, Z

    k_msleep(100);
  }
}

