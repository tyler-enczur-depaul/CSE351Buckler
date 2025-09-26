#include "gpio.h"

#define GPIO_ADDR 0x504

typedef struct {
    uint32_t OUT;
    uint32_t OUTSET;
    uint32_t OUTCLR;
    uint32_t IN;
    uint32_t DIR;
    uint32_t DIRSET;
    uint32_t DIRSET;
    uint32_t LATCH;
    uint32_t DETECTMODE;
    uint32_t* PIN_CNF;
} gpio_pins_t;

gpio_pints_t* gpio_pins = GPIO_ADDR;







// Inputs: 
//  gpio_num - gpio number 0-31
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
}

// Set gpio_num high
// Inputs: 
//  gpio_num - gpio number 0-31
void gpio_set(uint8_t gpio_num) {

}

// Set gpio_num low
// Inputs: 
//  gpio_num - gpio number 0-31
void gpio_clear(uint8_t gpio_num) {

}

// Inputs: 
//  gpio_num - gpio number 0-31
bool gpio_read(uint8_t gpio_num) {
    // should return pin state
    return 0;
}
