#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/i2c.h>

LOG_MODULE_REGISTER(i2c_scanner, LOG_LEVEL_INF);

#define I2C_DEV_LABEL DT_LABEL(DT_NODELABEL(i2c0))

void main(void)
{
    const struct device *i2c_dev = device_get_binding(I2C_DEV_LABEL);
    if (!i2c_dev) {
        LOG_ERR("I2C: Device driver not found.");
        return;
    }

    LOG_INF("Starting I2C scan on %s...", I2C_DEV_LABEL);

    for (uint8_t addr = 0x03; addr <= 0x77; addr++) {
        uint8_t dummy;
        int ret = i2c_write_read(i2c_dev, addr, NULL, 0, &dummy, 1);
        if (ret == 0) {
            LOG_INF("Found device at address 0x%02X", addr);
        }
        k_msleep(10);
    }

    LOG_INF("I2C scan complete.");
}