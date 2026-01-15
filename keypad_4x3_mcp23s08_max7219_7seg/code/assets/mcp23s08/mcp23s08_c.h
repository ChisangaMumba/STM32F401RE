#ifndef MCP23S08_C
#define MCP23S08_C
//------------------------------------------------------------------------------
#include "mcp23s08_h.h"            
//------------------------------------------------------------------------------
void mcp23s08_init(uint8_t devAddr, uint8_t portState)
{
	spi_init(1);		// SPI1 selected
	pinMode(CS2, OUTPUT, PUSH_PULL, NO_PU_PD);
	
	digitalWrite(CS2, HIGH);  // CS2 = 1; // deselect chip initially
	mcp23s08_write(devAddr, IODIR, portState);   
}
//------------------------------------------------------------------------------
void mcp23s08_write(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
  digitalWrite(CS2, LOW);   // CS2 = 0; // Chip Select: active low
 
  spi_write(devAddr | 0);		// WRITE 
  spi_write(regAddr);
	spi_write(data);
 
  digitalWrite(CS2, HIGH);  // CS2 = 1;
}
//------------------------------------------------------------------------------
uint8_t mcp23s08_read(uint8_t devAddr)
{
  uint8_t data = 0;

  digitalWrite(CS2, LOW);   // CS2 = 0;
  
	spi_write(devAddr | 1);		// READ
	spi_write(GPIO);
	data = spi_read();
  
  digitalWrite(CS2, HIGH);  // CS2 = 1;
  
  return data;
}
//------------------------------------------------------------------------------
#endif
