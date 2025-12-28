#ifndef MCP23017_C
#define MCP23017_C
//------------------------------------------------------------------------------
#include "mcp23017_h.h"            
//------------------------------------------------------------------------------
void mcp23017_init(uint8_t portStateA, uint8_t portStateB)
{
	i2c_init();
	
	mcp23017_write(IODIR_A, portStateA);   // only works if sent twice, why? still unkown.
	mcp23017_write(IODIR_A, portStateA);
	
	mcp23017_write(IODIR_B, portStateB);
	mcp23017_write(IODIR_B, portStateB);
}
//------------------------------------------------------------------------------
void mcp23017_write(uint8_t regAddr, uint8_t data)
{
  i2c_start();
 
  i2c_write(WRITE); 
  i2c_write(regAddr);
	i2c_write(data);
 
  i2c_stop();;
}
//------------------------------------------------------------------------------
uint8_t mcp23017_read(uint8_t port)
{
  uint8_t data = 0;

  i2c_start();
  
  i2c_write(WRITE);
	i2c_write(port);
	i2c_restart();
  i2c_write(READ);
	data = i2c_read(NACK);
  
  i2c_stop();
  
  return data;
}
//------------------------------------------------------------------------------
#endif
