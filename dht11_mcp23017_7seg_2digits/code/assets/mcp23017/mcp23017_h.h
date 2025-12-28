#ifndef MCP23S17_H
#define MCP23S17_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
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
//---------------------------Input pin Bit postions-----------------------------
#define I0         0x01
#define I1         0x02
#define I2         0x04
#define I3         0x08
#define I4         0x10
#define I5         0x20
#define I6         0x40
#define I7         0x80
//------------------------------------------------------------------------------
void    mcp23017_init(uint8_t portStateA, uint8_t portStateB);
void    mcp23017_write(uint8_t regAddr, uint8_t data);
uint8_t mcp23017_read(uint8_t port);               
//------------------------------------------------------------------------------
#endif
