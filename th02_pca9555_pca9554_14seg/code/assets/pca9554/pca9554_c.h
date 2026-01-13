#ifndef PCA9554_C
#define PCA9554_C
//------------------------------------------------------------------------------
#include "pca9554_h.h"            
//------------------------------------------------------------------------------
void pca9554_init(uint8_t devAddr, uint8_t portState)
{
	i2c_init();
	 
	pca9554_write(devAddr, PORT_CONFIG_REG, portState); 
}
//------------------------------------------------------------------------------
void pca9554_write(uint8_t devAddr, uint8_t regAddr, uint8_t portData)
{
  i2c_start();
 
  i2c_write(devAddr | 0);		// WRITE 
	i2c_write(regAddr);	
  i2c_write(portData);
 
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t pca9554_read(uint8_t devAddr, uint8_t portAddr, uint8_t pinNo)
{
  uint16_t data = 0;

  i2c_start();
  
  i2c_write(devAddr | 0);		// WRITE
	i2c_write(portAddr);
	i2c_restart();
	i2c_write(devAddr | 1);		// READ
	data = i2c_read(NACK);	
  
  i2c_stop();
  
  return (data  & (0x01 << pinNo)) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif
