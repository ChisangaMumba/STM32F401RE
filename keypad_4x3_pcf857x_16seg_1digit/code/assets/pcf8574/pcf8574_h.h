#ifndef PCF8574_H
#define PCF8574_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include "../i2c/soft_i2c_c.h"
//------------------------------------------------------------------------------
void    pcf8574_init(uint8_t devAddr, uint8_t portState);
void    pcf8574_write(uint8_t devAddr, uint8_t data);
uint8_t pcf8574_read(uint8_t port);               
//------------------------------------------------------------------------------
#endif
