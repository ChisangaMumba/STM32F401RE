#ifndef MCP23008_H
#define MCP23008_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//-----------------------I/O Direction Registers(TRIS)--------------------------
#define IODIR      0x00
//-----------------------General Purpose I/O------------------------------------
#define GPIO       0x09   //Reading the GPIOn register reads the value on the port.
//-----------------------Output Latches-----------------------------------------
#define OLAT       0x0A   //Writing to the OLATn register Writes to the associated port.
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
void    mcp23008_init(uint8_t portState);
void    mcp23008_write(uint8_t regAddr, uint8_t data);
uint8_t mcp23008_read(void);               
//------------------------------------------------------------------------------
#endif
