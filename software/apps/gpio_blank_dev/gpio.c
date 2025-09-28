#include "gpio.h"

gpio_manage_t* gpio_manage = (gpio_manage_t*)GPIO_ADDR;

// Inputs: 
//  gpio_num - gpio number 0-31
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
    uint32_t* pins = gpio_manage->PIN_CNF;
    if (dir == INPUT) {
        pins[gpio_num] = 0x2;
    }
    else {
        pins[gpio_num] = 0x5;
    }
}

// Set gpio_num high
// Inputs:
//  gpio_num - gpio number 0-31
void gpio_set(uint8_t gpio_num) {
    gpio_manage->OUTSET = (1 << gpio_num);
}

// Set gpio_num low
// Inputs:
//  gpio_num - gpio number 0-31
void gpio_clear(uint8_t gpio_num) {
    gpio_manage->OUTCLR = (1 << gpio_num);
}

// Inputs:
//  gpio_num - gpio number 0-31
bool gpio_read(uint8_t gpio_num) {
    return (bool)(gpio_manage->IN & (1 << gpio_num));
}
