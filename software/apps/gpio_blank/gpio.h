#pragma once

#include "nrf.h"
#include "stdbool.h"

#define GPIO_BASE_ADDR 0x504
#define GPIO_PIN_ADDR 0x700

typedef enum {
    INPUT = 0,
    OUTPUT,
} gpio_direction_t;

typedef struct {
    uint32_t OUT;
    uint32_t OUTSET;
    uint32_t OUTCLR;
    uint32_t IN;
    uint32_t DIR;
    uint32_t DIRSET;
    uint32_t DIRCLR;
    uint32_t LATCH;
    uint32_t DETECTMODE;
} gpio_manage_t;


// Inputs: 
//  gpio_num - gpio number 0-31
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir);

// Inputs: 
//  gpio_num - gpio number 0-31
void gpio_set(uint8_t gpio_num);

// Inputs: 
//  gpio_num - gpio number 0-31
void gpio_clear(uint8_t gpio_num);

// Inputs: 
//  gpio_num - gpio number 0-31
// Returns:
//  current state of the specified gpio pin
bool gpio_read(uint8_t gpio_num);
