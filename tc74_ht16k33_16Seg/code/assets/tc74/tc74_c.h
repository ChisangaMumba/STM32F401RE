#ifndef tc74_C
#define	tc74_C
//------------------------------------------------------------------------------
#include "tc74_h.h"
//------------------------------------------------------------------------------
void tc74_init(uint8_t data)
{
  i2c_init();
	tc74_config(data);
}
//------------------------------------------------------------------------------
void tc74_config(uint8_t data)
{
  i2c_start();                      
  
  i2c_write(READ);								//Datasheet says WRITE (0x9B), but that does NOT work              
  i2c_write(CONFIG_REG);                                      
  i2c_write(data);                
  
  i2c_stop();
}
//------------------------------------------------------------------------------
int8_t tc74_read(uint8_t regAddress)
{
	int8_t data = 0;
	
  i2c_start();                      
  
  i2c_write(READ);								//Datasheet says WRITE (0x9B), but that does NOT work 
  i2c_write(regAddress);           
  i2c_restart();                           
  i2c_write(WRITE);								//Datasheet says READ (0x9A), but that does NOT work                 
	data = i2c_read(NACK);
  
  i2c_stop();
  
  return data;
}
//------------------------------------------------------------------------------
int8_t tc74_readTemp(void)
{
  int8_t temp = tc74_read(TEMPR_REG);
    
  return temp;
}
//------------------------------------------------------------------------------
#endif
