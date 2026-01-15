#ifndef PCF8575_C
#define PCF8575_C
//------------------------------------------------------------------------------
#include "pcf8575_h.h"            
//------------------------------------------------------------------------------
void pcf8575_init(uint8_t devAddr, uint8_t portA_state, uint8_t portB_state)
{
	i2c_init();		// I2C1 selected

	pcf8575_write(devAddr, portA_state, portB_state);
}
//------------------------------------------------------------------------------
void pcf8575_write(uint8_t devAddr, uint8_t portA_state, uint8_t portB_state)
{
  i2c_start();
 
  i2c_write(devAddr | 0);		// WRITE 
  i2c_write(portA_state);
	i2c_write(portB_state);
 
  i2c_stop();
}
//------------------------------------------------------------------------------
uint16_t pcf8575_read(uint8_t devAddr)
{
  uint16_t data[2] = { 0, 0 };

  i2c_start(); 
  
	i2c_write(devAddr | 1);		// READ
	data[1] = i2c_read(ACK);	// MSB
	data[0] = i2c_read(NACK);	// LSB
  
	i2c_stop(); 
  
  return (data[1] << 8) | data[0];
}
//------------------------------------------------------------------------------
#endif


