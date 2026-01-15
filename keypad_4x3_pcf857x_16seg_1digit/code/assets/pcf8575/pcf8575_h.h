#ifndef PCF8575_H
#define PCF8575_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include "../i2c/soft_i2c_c.h"
//------------------------------------------------------------------------------
void    pcf8575_init(uint8_t devAddr, uint8_t portA_state, uint8_t portB_state);
void    pcf8575_write(uint8_t devAddr, uint8_t portA_state, uint8_t portB_state);
uint16_t pcf8575_read(uint8_t devAddr);               
//------------------------------------------------------------------------------
#endif
