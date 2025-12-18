#ifndef MAX6953_H
#define	MAX6953_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
//													Max6953 Registers
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x01
#define INTESITY_REG10      0x01
#define INTESITY_REG32      0x02
#define SCAN_LIMIT_REG      0x03
#define SHUTDOWN_REG        0x04
#define DISPLAY_TEST_REG    0x07
#define MAX6953_ADRR     		0xA0
//------------------------------------------------------------------------------
//													Max6953 Commands
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0xFF
#define SCAN_LOW_NIBBLE     0x03
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
#define DECIMAL_POINT       0x80
#define DISPLAY_REG0        0x20
//------------------------------------------------------------------------------
//													Max6953 Prototypes
//------------------------------------------------------------------------------
void max6953_init(void);
void max6953_config(void);
void max6953_write(uint8_t reg, uint8_t data);
void max6953_displayNumber(long number);
void max6953_displayText(char text[]);
void writeChar(char chr, uint8_t chrPos);
uint8_t getDigit(char chr);
uint8_t getCustomChar(char chrAscii);
inline uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
const char customChar[] = "£¥€°µ±";             //see Max6953 datasheet page 13 (Table 14. Character Map)
const char charCode[] = {24,25,26,27,28,29}; 
//------------------------------------------------------------------------------
#endif
