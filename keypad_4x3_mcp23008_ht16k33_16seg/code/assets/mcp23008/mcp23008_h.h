#ifndef MCP23008_H
#define MCP23008_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include "../i2c/soft_i2c_c.h"
//-----------------------I/O Direction Registers(TRIS)--------------------------
#define IODIR	    			0x00
//------------PULL-UP RESISTOR CONFIGURATION (GPPU) REGISTER--------------------
#define GPPU						0x06  // The GPPU register controls the pull-up resistors for the port pins. 
//-----------------------General Purpose I/O------------------------------------
#define GPIO	     			0x09   //Reading the GPIOn register reads the value on the port.
//-----------------------Output Latches-----------------------------------------
#define OLAT	     			0x0A   //Writing to the OLATn register Writes to the associated port.
//------------------------------------------------------------------------------
void    mcp23008_init(uint8_t devAddr, uint8_t portStateB);
void    mcp23008_write(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint8_t mcp23008_read(uint8_t devAddr);               
//------------------------------------------------------------------------------
#endif
