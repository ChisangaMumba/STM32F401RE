#ifndef MCP23S08_H
#define MCP23S08_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define CS1   PA3
//-----------------------I/O Direction Registers(TRIS)--------------------------
#define IODIR	    			0x00
//-----------------------General Purpose I/O------------------------------------
#define GPIO	     			0x09   //Reading the GPIOn register reads the value on the port.
//-----------------------Output Latches-----------------------------------------
#define OLAT	     			0x0A   //Writing to the OLATn register Writes to the associated port.
//------------------------------------------------------------------------------
void    mcp23s08_init(uint8_t devAddr, uint8_t portStateB);
void    mcp23s08_write(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint8_t mcp23s08_read(uint8_t port, uint8_t pinNo);               
//------------------------------------------------------------------------------
#endif
