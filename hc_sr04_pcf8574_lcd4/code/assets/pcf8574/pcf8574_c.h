#ifndef PCF8574_C
#define PCF8574_C
//------------------------------------------------------------------------------
#include "pcf8574_h.h"            
//------------------------------------------------------------------------------
void pcf8574_init(uint8_t portState)
{
  pcf8574_write(portState);
}
//------------------------------------------------------------------------------
void pcf8574_write(uint8_t data)
{
  i2c_start();
  
  i2c_write(PCF8574_ADDRESS); // Write operation
  i2c_write(data);
  
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t pcf8574_read(void)
{
  uint8_t data = 0;

  i2c_start();
  
  i2c_write(PCF8574_ADDRESS | 0x01); // Read operation
  data = i2c_read(NACK);
  
  i2c_stop();
  
  return data;
}
//------------------------------------------------------------------------------
#endif
