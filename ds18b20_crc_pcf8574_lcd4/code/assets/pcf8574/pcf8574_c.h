#ifndef PCF8574_C
#define PCF8574_C
//------------------------------------------------------------------------------
#include "pcf8574_h.h"            
//------------------------------------------------------------------------------
void pcf8574_init(uint8_t address, uint8_t portState)
{
	i2c_init(1);	// I2C1 selected
  pcf8574_write(address, portState);
}
//------------------------------------------------------------------------------
void pcf8574_write(uint8_t address, uint8_t data)
{
  i2c_start();
  
  i2c_address(address | 0); // Write operation
  i2c_write(data);
  
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t pcf8574_read(uint8_t address)
{
  uint8_t data = 0;

  i2c_start();
  
  i2c_address(address | 1); // Read operation
  data = i2c_read(NACK);
  
  i2c_stop();
  
  return data;
}
//------------------------------------------------------------------------------
#endif
