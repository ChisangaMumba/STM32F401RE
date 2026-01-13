#ifndef MCP23S17_H
#define MCP23S17_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define CS1   PA3
//-----------------------I/O Direction Registers(TRIS)--------------------------
#define IODIR_A    0x00
#define IODIR_B    0x01
//-----------------------General Purpose I/O------------------------------------
#define GPIO_A     0x12   //Reading the GPIOn register reads the value on the port.
#define GPIO_B     0x13
//-----------------------Output Latches-----------------------------------------
#define OLAT_A     0x14   //Writing to the OLATn register Writes to the associated port.
#define OLAT_B     0x15
//------------------------------------------------------------------------------
void    mcp23s17_init(uint8_t devAddr, uint8_t portA_state, uint8_t portB_state);
void    mcp23s17_write(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint8_t mcp23s17_read(uint8_t devAddr, uint8_t port, uint8_t pinNo);               
//------------------------------------------------------------------------------
#endif
