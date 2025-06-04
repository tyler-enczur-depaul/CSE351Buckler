// // MPU-9250 driver
// //
// // Read from MPU-9250 3-axis accelerometer/gyro/magnetometer over I2C
// // Register documentation: http://www.invensense.com/wp-content/uploads/2017/11/RM-MPU-9250A-00-v1.6.pdf
// //
// // Based on https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library/blob/master/src/util/inv_mpu.c

#include <stdbool.h>
#include <stdint.h>
#include<zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
// #include "app_error.h"
// #include "nrf.h"
// #include "nrf_delay.h"
// #include "nrf_drv_timer.h"
// #include "nrf_twi_mngr.h"

#include "mpu9250.h"

#define SLEEP_TIME_MS 1
#define SENSOR_NODE DT_NODELABEL(mpu9250_accel)

const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(SENSOR_NODE);


// static uint8_t MPU_ADDRESS = 0x68;
// static uint8_t MAG_ADDRESS = 0x0C;

// static const nrf_twi_mngr_t* i2c_manager = NULL;

// // rotation tracking variables
// static const nrf_drv_timer_t gyro_timer = NRFX_TIMER_INSTANCE(1);
// static mpu9250_measurement_t integrated_angle;
// static uint32_t prev_timer_val;

// static void gyro_timer_event_handler(nrf_timer_event_t event_type, void* p_context) {
//   // don't care about events
// }

// static uint8_t i2c_reg_read(uint8_t i2c_addr, uint8_t reg_addr) {
//   uint8_t rx_buf = 0;
//   nrf_twi_mngr_transfer_t const read_transfer[] = {
//     NRF_TWI_MNGR_WRITE(i2c_addr, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),
//     NRF_TWI_MNGR_READ(i2c_addr, &rx_buf, 1, 0),
//   };
//   ret_code_t error_code = nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);
//   APP_ERROR_CHECK(error_code);
//   return rx_buf;
// }

// static void i2c_reg_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t data) {
//   uint8_t buf[2] = {reg_addr, data};
//   nrf_twi_mngr_transfer_t const write_transfer[] = {
//     NRF_TWI_MNGR_WRITE(i2c_addr, buf, 2, 0),
//   };
//   ret_code_t error_code = nrf_twi_mngr_perform(i2c_manager, NULL, write_transfer, 1, NULL);
//   APP_ERROR_CHECK(error_code);
// }

//   i2c_manager = i2c;

//   // initialize a timer - the default frequency is 16MHz
//   nrf_drv_timer_config_t timer_cfg = {
//     .frequency          = NRF_TIMER_FREQ_1MHz,
//     .mode               = NRF_TIMER_MODE_TIMER,
//     .bit_width          = NRF_TIMER_BIT_WIDTH_32,
//     .interrupt_priority = NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY,
//     .p_context          = NULL,
//   };
//   //ret_code_t error_code = nrf_drv_timer_init(&gyro_timer, &timer_cfg, gyro_timer_event_handler);
//   ret_code_t error_code = nrfx_timer_init(&gyro_timer, &timer_cfg, gyro_timer_event_handler);
//   APP_ERROR_CHECK(error_code);

 

// initialization and configuration
// void mpu9250_init(cost nrf_twi_mngr_t* i2c) {
int mpu9250_init(){

if (!device_is_ready(dev_i2c.bus)) {
    printk("I2C device not ready\n");
    return -1;
}
printk("Ready to use the I2C device \n");
 // reset mpu
//   i2c_reg_write(MPU_ADDRESS, MPU9250_PWR_MGMT_1, 0x80);
// int ret;
uint8_t config_bytes[2];
int ret;

// Reset device
config_bytes[0] = MPU9250_PWR_MGMT_1;
config_bytes[1] = 0x80;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to reset MPU9250 (PWR_MGMT_1)\n");
    printk("Reset failed: error code = %d\n", ret);
    return ret;

}

k_msleep(100);

// Disable sleep mode
config_bytes[0] = MPU9250_PWR_MGMT_1;
config_bytes[1] = 0x00;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to disable sleep mode (PWR_MGMT_1)\n");
    return ret;
}

// Enable bypass mode
config_bytes[0] = MPU9250_USER_CTRL;
config_bytes[1] = 0x00;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to write USER_CTRL register\n");
    return ret;
}

k_msleep(3);

// Configure INT pin
config_bytes[0] = MPU9250_INT_PIN_CFG;
config_bytes[1] = 0x02;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to write INT_PIN_CFG register\n");
    return ret;
}

// Configure gyro range
config_bytes[0] = MPU9250_GYRO_CONFIG;
config_bytes[1] = 0x18;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to configure GYRO_CONFIG register\n");
    return ret;
}

// Configure accelerometer range
config_bytes[0] = MPU9250_ACCEL_CONFIG;
config_bytes[1] = 0x00;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to configure ACCEL_CONFIG register\n");
    return ret;
}

// Reset magnetometer
config_bytes[0] = AK8963_CNTL2;
config_bytes[1] = 0x01;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to reset AK8963 (CNTL2)\n");
    return ret;
}

k_msleep(100);

// Configure magnetometer for continuous measurement mode
config_bytes[0] = AK8963_CNTL1;
config_bytes[1] = 0x02;
ret = i2c_write_dt(&dev_i2c, config_bytes, sizeof(config_bytes));
if (ret < 0) {
    printk("Failed to set AK8963 to continuous measurement mode (CNTL1)\n");
    return ret;
}

return 0;
}

mpu9250_measurement_t mpu9250_read_accelerometer() {
  // read values
  

//   int16_t x_val = (((uint16_t)i2c_reg_read(MPU_ADDRESS, MPU9250_ACCEL_XOUT_H)) << 8) | i2c_reg_read(MPU_ADDRESS, MPU9250_ACCEL_XOUT_L);
//   int16_t y_val = (((uint16_t)i2c_reg_read(MPU_ADDRESS, MPU9250_ACCEL_YOUT_H)) << 8) | i2c_reg_read(MPU_ADDRESS, MPU9250_ACCEL_YOUT_L);
//   int16_t z_val = (((uint16_t)i2c_reg_read(MPU_ADDRESS, MPU9250_ACCEL_ZOUT_H)) << 8) | i2c_reg_read(MPU_ADDRESS, MPU9250_ACCEL_ZOUT_L);



int8_t x_val[2] = {0};  // [0] = low byte, [1] = high byte
int8_t y_val[2] = {0};
int8_t z_val[2] = {0};
int ret_code = 0;

// X-axis
ret_code = i2c_reg_read_byte_dt(&dev_i2c, MPU9250_ACCEL_XOUT_L, &x_val[0]);
if (ret_code < 0) {
    printk("Failed to read ACCEL_XOUT_L: %d\n", ret_code);
}

ret_code = i2c_reg_read_byte_dt(&dev_i2c, MPU9250_ACCEL_XOUT_H, &x_val[1]);
if (ret_code < 0) {
    printk("Failed to read ACCEL_XOUT_H: %d\n", ret_code);
}

// Y-axis
ret_code = i2c_reg_read_byte_dt(&dev_i2c, MPU9250_ACCEL_YOUT_L, &y_val[0]);
if (ret_code < 0) {
    printk("Failed to read ACCEL_YOUT_L: %d\n", ret_code);
}

ret_code = i2c_reg_read_byte_dt(&dev_i2c, MPU9250_ACCEL_YOUT_H, &y_val[1]);
if (ret_code < 0) {
    printk("Failed to read ACCEL_YOUT_H: %d\n", ret_code);
}

// Z-axis
ret_code = i2c_reg_read_byte_dt(&dev_i2c, MPU9250_ACCEL_ZOUT_L, &z_val[0]);
if (ret_code < 0) {
    printk("Failed to read ACCEL_ZOUT_L: %d\n", ret_code);
}

ret_code = i2c_reg_read_byte_dt(&dev_i2c,MPU9250_ACCEL_ZOUT_H, &z_val[1]);
if (ret_code < 0) {
    printk("Failed to read ACCEL_ZOUT_H: %d\n", ret_code);
}



//   int16_t x_val, y_val, z_val;

//   x_val = ((uint16_t)(x_val_h<<8) | x_val_l);
//   y_val = (y_val_h)<<8 | y_val_l;
//   z_val = (z_val_h)<<8 | z_val_l;
int16_t x = (int16_t)(((uint8_t)x_val[1] << 8) | (uint8_t)x_val[0]);
int16_t y = (int16_t)(((uint8_t)y_val[1] << 8) | (uint8_t)y_val[0]);
int16_t z = (int16_t)(((uint8_t)z_val[1] << 8) | (uint8_t)z_val[0]);
  // convert to g
  // coversion at +/- 2 g is 16384 LSB/g
  mpu9250_measurement_t measurement = {0};
  measurement.x_axis = ((float)x) / 16384;
  measurement.y_axis = ((float)y) / 16384;
  measurement.z_axis = ((float)z) / 16384;
  
//   printk("x_axis: %f, y_axis: %f, z_axis: %f\n", measurement.x_axis, measurement.y_axis, measurement.z_axis);
  return measurement;
}

// mpu9250_measurement_t mpu9250_read_gyro() {
//   // read values
//   int16_t x_val = (((uint16_t)i2c_reg_read(MPU_ADDRESS, MPU9250_GYRO_XOUT_H)) << 8) | i2c_reg_read(MPU_ADDRESS, MPU9250_GYRO_XOUT_L);
//   int16_t y_val = (((uint16_t)i2c_reg_read(MPU_ADDRESS, MPU9250_GYRO_YOUT_H)) << 8) | i2c_reg_read(MPU_ADDRESS, MPU9250_GYRO_YOUT_L);
//   int16_t z_val = (((uint16_t)i2c_reg_read(MPU_ADDRESS, MPU9250_GYRO_ZOUT_H)) << 8) | i2c_reg_read(MPU_ADDRESS, MPU9250_GYRO_ZOUT_L);

//   // convert to g
//   // coversion at +/- 2000 degrees/second is 16.4 LSB/g
//   mpu9250_measurement_t measurement = {0};
//   measurement.x_axis = ((float)x_val) / 16.4;
//   measurement.y_axis = ((float)y_val) / 16.4;
//   measurement.z_axis = ((float)z_val) / 16.4;
//   return measurement;
// }

// mpu9250_measurement_t mpu9250_read_magnetometer() {

//   // read data
//   // must read 8 bytes starting at the first status register
//   uint8_t reg_addr = AK8963_ST1;
//   uint8_t rx_buf[8] = {0};
//   nrf_twi_mngr_transfer_t const read_transfer[] = {
//     NRF_TWI_MNGR_WRITE(MAG_ADDRESS, &reg_addr, 1, NRF_TWI_MNGR_NO_STOP),
//     NRF_TWI_MNGR_READ(MAG_ADDRESS, rx_buf, 8, 0),
//   };
//   ret_code_t error_code = nrf_twi_mngr_perform(i2c_manager, NULL, read_transfer, 2, NULL);
//   APP_ERROR_CHECK(error_code);

//   // determine values
//   int16_t x_val = (((uint16_t)rx_buf[2]) << 8) | rx_buf[1];
//   int16_t y_val = (((uint16_t)rx_buf[4]) << 8) | rx_buf[3];
//   int16_t z_val = (((uint16_t)rx_buf[6]) << 8) | rx_buf[5];

//   // convert to g
//   // coversion is 0.6 uT/LSB
//   mpu9250_measurement_t measurement = {0};
//   measurement.x_axis = ((float)x_val) * 0.6;
//   measurement.y_axis = ((float)y_val) * 0.6;
//   measurement.z_axis = ((float)z_val) * 0.6;

//   return measurement;
// }

// ret_code_t mpu9250_start_gyro_integration() {
//   if (nrfx_timer_is_enabled(&gyro_timer)) {
//     return NRF_ERROR_INVALID_STATE;
//   }

//   // zero the angle
//   integrated_angle.z_axis = 0;
//   integrated_angle.y_axis = 0;
//   integrated_angle.x_axis = 0;

//   nrfx_timer_clear(&gyro_timer);
//   nrfx_timer_enable(&gyro_timer);
//   prev_timer_val = 0;

//   return NRF_SUCCESS;
// }

// void mpu9250_stop_gyro_integration() {
//   nrfx_timer_disable(&gyro_timer);
// }

// mpu9250_measurement_t mpu9250_read_gyro_integration() {
//   uint32_t curr_timer_val = nrfx_timer_capture(&gyro_timer, NRF_TIMER_CC_CHANNEL0);
//   float time_diff = ((float)(curr_timer_val - prev_timer_val))/1000000.0;
//   //printf("curr %lu prev %lu diff %f\n", curr_timer_val, prev_timer_val, time_diff);
//   prev_timer_val = curr_timer_val;
//   mpu9250_measurement_t measure = mpu9250_read_gyro();
//   if (measure.z_axis > 0.5 || measure.z_axis < -0.5) {
//     integrated_angle.z_axis += measure.z_axis*time_diff;
//   }
//   if (measure.x_axis > 0.5 || measure.x_axis < -0.5) {
//     integrated_angle.x_axis += measure.x_axis*time_diff;
//   }
//   if (measure.y_axis > 0.5 || measure.y_axis < -0.5) {
//     integrated_angle.y_axis += measure.y_axis*time_diff;
//   }
//   return integrated_angle;
// }

