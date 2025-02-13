#include "gpio.h"                                                                                                                                                                                           
                                                                                
// Inputs:                                                                      
//  gpio_num - gpio number 0-31                                                 
//  dir - gpio direction (INPUT, OUTPUT)                                        
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {                      
  uint32_t addr = 0x0000;                                                       
  
  
  if (dir == 0) {                                                               
    addr = 0x5000051c; // DIR_CLR                                               
    uint32_t *ptr = (uint32_t *)addr;                                                                                                                           
    *ptr = (1/*dir*/ << gpio_num);      
  } else {                           

    addr = 0x50000518; // DIR_SET                                               
    uint32_t *ptr = (uint32_t *)addr;                                           
    *ptr = (1/*dir*/ << gpio_num);                                                
  }                                                                             
                                                                                                                                                              
  
}                                                                               
                                                                                
                                                                                
// Set gpio_num high                                                            
// Inputs:                                                                      
//  gpio_num - gpio number 0-31                                                 
void gpio_set(uint8_t gpio_num) {                                               
  uint32_t addr = 0x50000508; // OUTSET                                         
  uint32_t *ptr = (uint32_t *)addr;                                             
                                                                                
  *ptr = (1 << gpio_num);                                                       
}                                                                               
                                                                                
// Set gpio_num low                                                             
// Inputs:                                                                      
//  gpio_num - gpio number 0-31                                                 
void gpio_clear(uint8_t gpio_num) {                                             
  uint32_t addr = 0x5000050c; // OUTCLR                                         
  uint32_t *ptr = (uint32_t *)addr;                                             
                                                                                
  *ptr = (1 << gpio_num);                                                       
}                                                                               
                                                                                
// Inputs:                                                                      
//  gpio_num - gpio number 0-31                                                 
bool gpio_read(uint8_t gpio_num) {                                              
  // should return pin state                                                    
  uint32_t addr = 0x50000510; // IN                                             
  uint32_t *ptr = (uint32_t *)addr;                                             
                                                   

  uint32_t *DIR_ptr = (uint32_t *) 0x50000514;
  printf("DIR Reg: %X \n", *DIR_ptr);

  printf("IN Reg: %X \n", *ptr);
  return *ptr & (1 << gpio_num) /*>> gpio_num*/;

  //return *ptr & (0xFFFFFFFF) /*>> gpio_num*/;
}