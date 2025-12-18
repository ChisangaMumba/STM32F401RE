#ifndef MCP23008_C
#define MCP23008_C
//------------------------------------------------------------------------------
#include "mcp23008_h.h"            
//------------------------------------------------------------------------------
void mcp23008_init(uint8_t portState)
{
	i2c_init();
  mcp23008_write(IODIR, portState);
}
//------------------------------------------------------------------------------
void mcp23008_write(uint8_t regAddr, uint8_t data)
{
  i2c_start();
  
  i2c_write(WRITE); 
  i2c_write(regAddr);
	i2c_write(data);
  
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t mcp23008_read(void)
{
  uint8_t data = 0;

  i2c_start();
  
  i2c_write(WRITE);
	i2c_write(OLAT);
	i2c_restart();
  i2c_write(READ);
	data = i2c_read(NACK);
  
  i2c_stop();
  
  return data;
}
//------------------------------------------------------------------------------
#endif
