#ifndef MAX6952_H
#define	MAX6952_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
//------------------------------------------------------------------------------
#define CS  PA3 
//------------------------------------------------------------------------------
//															Max6952 Registers
//------------------------------------------------------------------------------
#define NO_OP_REG           0x00     //Used for Max6952 Cascading purposes
#define DECODE_MODE_REG     0x01
#define INTESITY_REG10      0x01
#define INTESITY_REG32      0x02
#define SCAN_LIMIT_REG      0x03
#define SHUTDOWN_REG        0x04
#define DISPLAY_TEST_REG    0x07
//------------------------------------------------------------------------------
//															Max6952 Commands
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
//															Max6952 Prototypes
//------------------------------------------------------------------------------
void max6952_init(uint8_t noChips);
void max6952_config(uint8_t chip);
void max6952_write(uint8_t reg, uint8_t data, uint8_t chip);
void max6952_displayNumber(long number);
void max6952_displayText(char text[]);
void max6952_NoOperation(void);
void writeChar(char chr, uint8_t chrPos);
uint8_t getDigit(char chr);
uint8_t getCustomChar(char chrAscii);
inline uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
const char 		customChar[] = "£¥€°µ±";             //see Max6952 datasheet page 13 (Table 14. Character Map)
const uint8_t charCode[] = {24,25,26,27,28,29}; 
//------------------------------------------------------------------------------
#endif
