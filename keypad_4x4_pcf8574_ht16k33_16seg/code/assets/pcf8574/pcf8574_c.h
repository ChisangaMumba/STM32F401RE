#ifndef PCF8574_C
#define PCF8574_C
//------------------------------------------------------------------------------
#include "pcf8574_h.h"            
//------------------------------------------------------------------------------
void pcf8574_init(uint8_t devAddr, uint8_t portState)
{
	i2c_init();		// I2C1 selected

	pcf8574_write(devAddr, portState);   
}
//------------------------------------------------------------------------------
void pcf8574_write(uint8_t devAddr, uint8_t data)
{
  i2c_start();
 
  i2c_write(devAddr | 0);		// WRITE 
	i2c_write(data);
 
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t pcf8574_read(uint8_t devAddr)
{
  uint8_t data = 0;

  i2c_start();
  
	i2c_write(devAddr | 1);		// READ
	data = i2c_read(NACK);
  
  i2c_stop();
  
  return data;
}
//------------------------------------------------------------------------------
#endif
