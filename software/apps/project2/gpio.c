#include "gpio.h"

gpio_manage_t* gpio_manage = (gpio_manage_t*)GPIO_ADDR;

// Inputs: 
//  gpio_num - gpio number 0-31
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
    uint32_t* pins = gpio_manage->PIN_CNF;
    if (dir == INPUT) {
        pins[gpio_num] = 0b1100;
    }
    else {
        printf("%p\n", pins+gpio_num);
        pins[gpio_num] = 0b111;
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


void gpio_OUT(uint8_t pin_numb, int val){
    //printf("Using OUT Register to write: %d on pin: %d \n", val, pin_numb);
    uint32_t address = 0x50000000 + 0x700 + 0x504; // loading OUT register
    uint32_t *ptr = (uint32_t *) address;
    //printf("Address being written at is: %x \n", 0xFFFFFFFF||val<<pin_numb);
    *ptr &=val<<pin_numb;  // Read the contents of the register and clear a necessary bit
}



void gpio_toggle(uint8_t pin_numb){

  uint32_t address = 0x50000000 + 0x700 + 0x504; // loading OUT register
  uint32_t *ptr = (uint32_t *) address;
  *ptr^=1<<pin_numb;
}
