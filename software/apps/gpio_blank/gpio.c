#include "gpio.h"

gpio_manage_t* gpio_manage = (uint32_t*)GPIO_BASE_ADDR;
uint32_t* gpio_pins = (uint32_t*)GPIO_PIN_ADDR;

// Inputs: 
//  gpio_num - gpio number 0-31
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
    if (dir == INPUT) {
        gpio_manage->DIRCLR |= 1 << gpio_num;
    }
    else {
        gpio_manage->DIRSET |= 1 << gpio_num;
    }
}

// Set gpio_num high
// Inputs: 
//  gpio_num - gpio number 0-31
void gpio_set(uint8_t gpio_num) {
    gpio_manage->OUTSET |= (1 << gpio_num);
}

// Set gpio_num low
// Inputs: 
//  gpio_num - gpio number 0-31
void gpio_clear(uint8_t gpio_num) {
    gpio_manage->OUTCLR |= (1 << gpio_num);
}

// Inputs: 
//  gpio_num - gpio number 0-31
bool gpio_read(uint8_t gpio_num) {
    // should return pin state
    return (bool)(gpio_manage->IN & (1 << gpio_num));
}
