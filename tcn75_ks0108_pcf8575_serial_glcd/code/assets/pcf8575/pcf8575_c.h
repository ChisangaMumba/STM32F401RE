#ifndef PCF8575_C
#define PCF8575_C
//------------------------------------------------------------------------------
#include "pcf8575_h.h"            
//------------------------------------------------------------------------------
void pcf8575_init(uint8_t portStateA, uint8_t portStateB)
{
	i2c_init();
	
	pcf8575_write(portStateA, portStateB); 
}
//------------------------------------------------------------------------------
void pcf8575_write(uint8_t portA, uint8_t portB)
{
  i2c_start();
 
  i2c_write(WRITE); 
  i2c_write(portA);
	i2c_write(portB);
 
  i2c_stop();;
}
//------------------------------------------------------------------------------
uint16_t pcf8575_read(void)
{
  uint16_t data[2];

  i2c_start();
  
  i2c_write(READ);
  data[1] = i2c_write(ACK);		// MSB
	data[0] = i2c_read(NACK);		// LSB
  
  i2c_stop();
  
  return (data[1] << 8) | data[0];
}
//------------------------------------------------------------------------------
#endif
