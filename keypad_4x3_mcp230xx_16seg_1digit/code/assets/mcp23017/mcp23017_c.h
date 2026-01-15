#ifndef MCP23017_C
#define MCP23017_C
//------------------------------------------------------------------------------
#include "mcp23017_h.h"            
//------------------------------------------------------------------------------
void mcp23017_init(uint8_t devAddr, uint8_t portA_state, uint8_t portB_state)
{
	i2c_init();		// I2C1 selected

	mcp23017_write(devAddr, IODIR_A, portA_state);
	mcp23017_write(devAddr, IODIR_B, portB_state);	
}
//------------------------------------------------------------------------------
void mcp23017_write(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
  i2c_start();
 
  i2c_write(devAddr | 0);		// WRITE 
  i2c_write(regAddr);
	i2c_write(data);
 
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t mcp23017_read(uint8_t devAddr, uint8_t port)
{
  uint8_t data = 0;

  i2c_start(); 
  
	i2c_write(devAddr | 0);		// WRITE
	i2c_write(port);
	i2c_restart();
	i2c_write(devAddr | 1);		// READ
	data = i2c_read(NACK);
  
	i2c_stop(); 
  
  return data;
}
//------------------------------------------------------------------------------
#endif
