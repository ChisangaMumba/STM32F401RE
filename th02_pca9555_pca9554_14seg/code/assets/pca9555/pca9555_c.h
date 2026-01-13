#ifndef PCA9555_C
#define PCA9555_C
//------------------------------------------------------------------------------
#include "pca9555_h.h"            
//------------------------------------------------------------------------------
void pca9555_init(uint8_t devAddr, uint8_t portStateA, uint8_t portStateB)
{
	i2c_init();
	
	pca9555_write16(devAddr, PORTA_CONFIG, portStateA, portStateB); 
}
//------------------------------------------------------------------------------
void pca9555_write8(uint8_t devAddr, uint8_t regAddr, uint8_t portData)
{
  i2c_start();
 
  i2c_write(devAddr | 0);			// WRITE
	i2c_write(regAddr);	
  i2c_write(portData);
 
  i2c_stop();
}
//------------------------------------------------------------------------------
void pca9555_write16(uint8_t devAddr, uint8_t regAddr, uint8_t portA_data, uint8_t portB_data)
{
  i2c_start();
 
  i2c_write(devAddr | 0);			// WRITE
	i2c_write(regAddr);	
  i2c_write(portA_data);
	i2c_write(portB_data);
 
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t pca9555_read8(uint8_t devAddr, uint8_t portAddr)
{
  uint16_t data;

  i2c_start();
  
  i2c_write(devAddr | 0);			// WRITE
	i2c_write(portAddr);
	i2c_restart();
	i2c_write(devAddr | 1);			// READ
	data = i2c_read(NACK);	
  
  i2c_stop();
  
  return data;
}
//------------------------------------------------------------------------------
uint16_t pca9555_read16(uint8_t devAddr)
{
  uint16_t data[2];

  i2c_start();
  
  i2c_write(devAddr | 0);			// WRITE
	i2c_write(PORTA_RD);
	i2c_restart();
	i2c_write(devAddr | 1);			// READ
  data[0] = i2c_write(ACK);		// MSB  PORT A
	data[1] = i2c_read(NACK);		// LSB  PORT B
  
  i2c_stop();
  
  return (data[0] << 8) | data[1];
}
//------------------------------------------------------------------------------
#endif
