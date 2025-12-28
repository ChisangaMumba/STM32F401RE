#ifndef PCF8575_H
#define PCF8575_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//-----------------------W/R Control bytes--------------------------------------
#define WRITE      0x4E   // 0b0100 + 0b111(Slave address) + 0b0(Write) => 0x4E
#define READ       0x4F
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
void     pcf8575_init(uint8_t portStateA, uint8_t portStateB);
void     pcf8575_write(uint8_t regAddr, uint8_t data);
uint16_t pcf8575_read(void);               
//------------------------------------------------------------------------------
#endif
