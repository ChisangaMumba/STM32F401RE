#ifndef DS1620_PROTOTYPES_H
#define	DS1620_PROTOTYPES_H
//------------------------------------------------------------------------------
#include "threeWire.h"
//------------------------------------------------------------------------------
//ds1620 Commands
#define WRITE_TH              0x01
#define WRITE_TL              0x02
#define WRITE_CONFIG          0x0C
#define READ_COUNTER          0xA0
#define READ_TH               0xA1
#define READ_TL               0xA2
#define READ_SLOPE            0xA9
#define READ_TEMP            	0xAA
#define READ_CONFIG           0xAC
#define STOP_CONV             0x22
#define START_CONV            0xEE
//------------------------------------------------------------------------------
//Configuration Status
#define WRITE_SUCCESSFUL      0x00
#define WRITE_UNSUCCESSFUL    0x01
#define BAD_CONFIG            0x02
//------------------------------------------------------------------------------
void ds1620_init(int8_t tempH, int8_t tempL);
int16_t ds1620_read(uint8_t command);
uint8_t ds1620_writeConfig(uint8_t data_);
void ds1620_writeT_HL(uint8_t command, int8_t data_);
void ds1620_convert(uint8_t command);
float ds1620_getTempFloat(void);
int16_t ds1620_getTemp(uint8_t command);
int16_t calcTempr(int16_t tempr);
//------------------------------------------------------------------------------
#endif
