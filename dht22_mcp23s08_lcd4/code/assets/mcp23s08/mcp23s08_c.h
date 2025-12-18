#ifndef MCP23S08_C
#define MCP23S08_C
//------------------------------------------------------------------------------
#include "mcp23s08_h.h"            
//------------------------------------------------------------------------------
void mcp23s08_init(uint8_t portState)
{
	spi_init();
	pinMode(CS1, OUTPUT, PUSH_PULL);
	
	mcp23s08_write(IODIR, portState);   // only works if sent twice, why? still unkown.
	mcp23s08_write(IODIR, portState);
}
//------------------------------------------------------------------------------
void mcp23s08_write(uint8_t regAddr, uint8_t data)
{
  digitalWrite(CS1, LOW);   // CS1 = 0; // Chip Select: active low
 
  spi_write(WRITE); 
  spi_write(regAddr);
	spi_write(data);
 
  digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
uint8_t mcp23s08_read(void)
{
  uint8_t data = 0;

  digitalWrite(CS1, LOW);   // CS1 = 0;
  
	spi_write(READ);
	spi_write(GPIO);
	data = spi_read();
  
  digitalWrite(CS1, HIGH);  // CS1 = 1;
  
  return data;
}
//------------------------------------------------------------------------------
#endif
