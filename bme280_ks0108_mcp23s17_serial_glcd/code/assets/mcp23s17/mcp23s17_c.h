#ifndef MCP23S17_C
#define MCP23S17_C
//------------------------------------------------------------------------------
#include "mcp23s17_h.h"            
//------------------------------------------------------------------------------
void mcp23s17_init(uint8_t portStateA, uint8_t portStateB)
{
	spi_init();
	pinMode(CS1, OUTPUT, PUSH_PULL);
	
	mcp23s17_write(IODIR_A, portStateA);   // only works if sent twice, why? still unkown.
	mcp23s17_write(IODIR_A, portStateA);
	
	mcp23s17_write(IODIR_B, portStateB);
	mcp23s17_write(IODIR_B, portStateB);
}
//------------------------------------------------------------------------------
void mcp23s17_write(uint8_t regAddr, uint8_t data)
{
  digitalWrite(CS1, LOW);   // CS1 = 0; // Chip Select: active low
 
  spi_write(WRITE); 
  spi_write(regAddr);
	spi_write(data);
 
  digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
uint8_t mcp23s17_read(uint8_t port)
{
  uint8_t data = 0;

  digitalWrite(CS1, LOW);   // CS1 = 0;
  
	spi_write(READ);
	spi_write(port);
	data = spi_read();
  
  digitalWrite(CS1, HIGH);  // CS1 = 1;
  
  return data;
}
//------------------------------------------------------------------------------
#endif
