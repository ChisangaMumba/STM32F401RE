#ifndef MCP23S17_C
#define MCP23S17_C
//------------------------------------------------------------------------------
#include "mcp23s17_h.h"            
//------------------------------------------------------------------------------
void mcp23s17_init(uint8_t devAddr, uint8_t chipNum)
{
	spi_init(1);		// SPI1 selected
	pinMode(chips[chipNum], OUTPUT, PUSH_PULL, NO_PU_PD);
	
	digitalWrite(chips[chipNum], HIGH);  // CS = 1; // deselect chip initially	
}
//------------------------------------------------------------------------------
void mcp23s17_write(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t chipNum)
{
  digitalWrite(chips[chipNum], LOW);   // CS = 0; // Chip Select: active low
 
  spi_write(devAddr | 0);		// WRITE 
  spi_write(regAddr);
	spi_write(data);
 
  digitalWrite(chips[chipNum], HIGH);  // CS = 1;
}
//------------------------------------------------------------------------------
uint8_t mcp23s17_read(uint8_t devAddr, uint8_t port, uint8_t chipNum)
{
  uint8_t data = 0;

  digitalWrite(chips[chipNum], LOW);   // CS = 0;
  
	spi_write(devAddr | 1);		// READ
	spi_write(port);
	data = spi_read();
  
  digitalWrite(chips[chipNum], HIGH);  // CS = 1;
  
  return data;
}
//------------------------------------------------------------------------------
#endif

