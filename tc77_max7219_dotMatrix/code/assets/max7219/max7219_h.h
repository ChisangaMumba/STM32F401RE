#ifndef MAX7219_H
#define	MAX7219_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define CS  PA3 
//------------------------------------------------------------------------------
//															Max7219 Registers
//------------------------------------------------------------------------------
#define NO_OP_REG           0x00     //Used for Max7219 Cascading purposes
#define DECODE_MODE_REG     0x09
#define INTESITY_REG        0x0A
#define SCAN_LIMIT_REG      0x0B
#define SHUTDOWN_REG        0x0C
#define DISPLAY_TEST_REG    0x0F
//------------------------------------------------------------------------------
//															Max7219 Commands
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0x0F
#define SCAN_ALL_DIGITS     0x07   
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
//------------------------------------------------------------------------------
//															Max7219 Prototypes
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips);
void max7219_config(uint8_t chip);
void max7219_write(uint8_t reg, uint8_t data, uint8_t chip);
void max7219_displayNumber(long number);
void max7219_displayText(char text[]);
void max7219_NoOperation(void);
void writeChar(uint8_t chr, uint8_t chip);
void displayDp(uint8_t chr, uint8_t chip);
uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
#endif
