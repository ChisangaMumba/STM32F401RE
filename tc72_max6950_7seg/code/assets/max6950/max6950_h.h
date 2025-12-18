#ifndef MAX6950_H
#define	MAX6950_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define CS  PA3 
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x01
#define INTESITY_REG        0x02
#define SCAN_LIMIT_REG      0x03
#define SHUTDOWN_REG        0x04
#define DISPLAY_TEST_REG    0x07
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0x0F
#define SCAN_LOW_NIBBLE     0x03
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
#define DECIMAL_POINT       0x80
#define DISPLAY_REG0        0x20
//------------------------------------------------------------------------------
void 		max6950_init(uint8_t scanSize);
void 		max6950_write(uint8_t reg, uint8_t data);
void 		max6950_displayNumber(long number);
void 		max6950_displayText(char text[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t  dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void 		setDpPos(int8_t dpPos[], char chars[]);
uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
#endif
