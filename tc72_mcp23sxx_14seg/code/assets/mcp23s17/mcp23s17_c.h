#ifndef MCP23S17_C
#define MCP23S17_C
//------------------------------------------------------------------------------
#include "mcp23s17_h.h"            
//------------------------------------------------------------------------------
void mcp23s17_init(uint8_t devAddr, uint8_t portA_state, uint8_t portB_state)
{
	spi_init();
	pinMode(CS1, OUTPUT, PUSH_PULL);
	
	digitalWrite(CS1, HIGH);  // CS1 = 1; // deselect chip initially
	mcp23s17_write(devAddr, IODIR_A, portA_state);
	mcp23s17_write(devAddr, IODIR_B, portB_state);	
}
//------------------------------------------------------------------------------
void mcp23s17_write(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
  digitalWrite(CS1, LOW);   // CS1 = 0; // Chip Select: active low
 
  spi_write(devAddr | 0);		// WRITE 
  spi_write(regAddr);
	spi_write(data);
 
  digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
uint8_t mcp23s17_read(uint8_t devAddr, uint8_t port, uint8_t pinNo)
{
  uint8_t data = 0;

  digitalWrite(CS1, LOW);   // CS1 = 0;
  
	spi_write(devAddr | 1);		// READ
	spi_write(port);
	data = spi_read();
  
  digitalWrite(CS1, HIGH);  // CS1 = 1;
  
  return (data  & (0x01 << pinNo)) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif
