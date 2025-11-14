// Display app
//
// Write messages to a Newhaven OLED display over SPI

// Task: Modify the following application to obtain the values from an I2C sensor and display on the display

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>  // needed for tilt angle calculation

#include "app_error.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"
#include "nrf_twi_mngr.h"
#include "nrfx_gpiote.h"
#include "nrf_drv_spi.h"

#include "buckler.h"
#include "display.h"
#include "lsm9ds1.h"

#define RAD2DEG 57.29577951308232

NRF_TWI_MNGR_DEF(twi_mngr_instance, 5, 0);

float clamp_value(float val) {
    if (val > 1) {
        return 1;
    }
    if (val < -1) {
        return -1;
    }
    return val;
}

int main(void) {
    ret_code_t error_code = NRF_SUCCESS;

    // initialize RTT library
    error_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(error_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
    printf("Log initialized\n");

    // initialize i2c master (two wire interface)
    nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
    i2c_config.scl = BUCKLER_SENSORS_SCL;
    i2c_config.sda = BUCKLER_SENSORS_SDA;
    i2c_config.frequency = NRF_TWIM_FREQ_100K;
    error_code = nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);
    APP_ERROR_CHECK(error_code);

    // initialize LSM9DS1 driver
    lsm9ds1_init(&twi_mngr_instance);
    printf("lsm9ds1 initialized\n");

    lsm9ds1_start_gyro_integration();

    // initialize spi master(controller)
    nrf_drv_spi_t spi_instance = NRF_DRV_SPI_INSTANCE(1);
    nrf_drv_spi_config_t spi_config = {
        .sck_pin = BUCKLER_LCD_SCLK,
        .mosi_pin = BUCKLER_LCD_MOSI,
        .miso_pin = BUCKLER_LCD_MISO,
        .ss_pin = BUCKLER_LCD_CS,
        .irq_priority = NRFX_SPI_DEFAULT_CONFIG_IRQ_PRIORITY,
        .orc = 0,
        .frequency = NRF_DRV_SPI_FREQ_4M,
        .mode = NRF_DRV_SPI_MODE_2,
        .bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST
    };
    error_code = nrf_drv_spi_init(&spi_instance, &spi_config, NULL, NULL);
    APP_ERROR_CHECK(error_code);

    // initialize display driver
    display_init(&spi_instance);

    // Write test numbers in a loop
    char buf[16] = {0};
    while(1) {
        lsm9ds1_measurement_t acc_measurement = lsm9ds1_read_accelerometer();

        float angle = RAD2DEG * acos(clamp_value(acc_measurement.z_axis));
        if (angle < 45) {
            snprintf(buf, 16, "Tilt Angle:");
            display_write(buf, 0);
            snprintf(buf, 16, "%.3f", angle);
            display_write(buf, 1);
        }
        else {
            snprintf(buf, 16, "!!! DANGER OF");
            display_write(buf, 0);
            snprintf(buf, 16, "OVERTURN !!!");
            display_write(buf, 1);

        }
        nrf_delay_ms(500);


    }
}

