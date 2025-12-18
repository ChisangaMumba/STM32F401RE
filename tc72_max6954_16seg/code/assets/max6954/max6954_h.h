#ifndef MAX6954_H
#define	MAX6954_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
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
void 		max6954_init(void);
void 		max6954_write(uint8_t reg, uint8_t data);
void 		max6954_displayNumber(long number);
void 		max6954_displayText(char text[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t  dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void 		setDpPos(int8_t dpPos[], char chars[]);
uint8_t getCustomChar(char chrAscii);
inline	uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
const char		customChar[] = "£¥€°µ±";             //see Max6954 datasheet page 13 (Table 14. Character Map)
const uint8_t charCode[] = {24,25,26,27,28,29};
//------------------------------------------------------------------------------
#endif
