#ifndef MCP23008_C
#define MCP23008_C
//------------------------------------------------------------------------------
#include "mcp23008_h.h"            
//------------------------------------------------------------------------------
void mcp23008_init(uint8_t devAddr, uint8_t portState)
{
	i2c_init();

	mcp23008_write(devAddr, IODIR, portState);   
}
//------------------------------------------------------------------------------
void mcp23008_write(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
  i2c_start();   
 
  i2c_write(devAddr | 0);		// WRITE 
  i2c_write(regAddr);
	i2c_write(data);
 
  i2c_stop(); 
}
//------------------------------------------------------------------------------
uint8_t mcp23008_read(uint8_t devAddr, uint8_t pinNo)
{
  uint8_t data = 0;

  i2c_start();   
  
	i2c_write(devAddr | 0);		// WRITE
	i2c_write(OLAT);
	i2c_restart();
	i2c_write(devAddr | 1);		// READ
	data = i2c_read(NACK);
  
  i2c_stop();  
  
  return (data  & (0x01 << pinNo)) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif
