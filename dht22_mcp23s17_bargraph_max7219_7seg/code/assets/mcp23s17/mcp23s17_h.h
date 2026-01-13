#ifndef MCP23S17_H
#define MCP23S17_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define CS2   PA4
//-----------------------I/O Direction Registers(TRIS)--------------------------
#define IODIR_A    0x00
#define IODIR_B    0x01
//-----------------------General Purpose I/O------------------------------------
#define GPIO_A     0x12   //Reading the GPIOn register reads the value on the port.
#define GPIO_B     0x13
//-----------------------Output Latches-----------------------------------------
#define OLAT_A     0x14   //Writing to the OLATn register Writes to the associated port.
#define OLAT_B     0x15
//-----------------------W/R Control bytes--------------------------------------
#define WRITE      0x40   // 0b0100 + 0b000(Slave address) + 0b0(Write) => 0x40
#define READ       0x41
//------------------------------------------------------------------------------
void    mcp23s17_init(uint8_t portStateA, uint8_t portStateB);
void    mcp23s17_write(uint8_t regAddr, uint8_t data);
uint8_t mcp23s17_read(uint8_t port);               
//------------------------------------------------------------------------------
#endif
