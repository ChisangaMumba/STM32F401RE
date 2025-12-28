#ifndef MAX7219_H
#define	MAX7219_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../spi/soft_spi.h"
//------------------------------------------------------------------------------
#define CS  PA6 
//------------------------------------------------------------------------------
#define NO_OP_REG           0x00		// Used for max7219 Cascading purposes
#define DECODE_MODE_REG     0x09
#define INTESITY_REG        0x0A
#define SCAN_LIMIT_REG      0x0B
#define SHUTDOWN_REG        0x0C
#define DISPLAY_TEST_REG    0x0F
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0x0F
//
#define SCAN_LIM0		     		0x00		// Display digit  0 only
#define SCAN_LIM1     			0x01		// Display digits 0 and 1
#define SCAN_LIM2     			0x02		// Display digits 0 and 1 2
#define SCAN_LIM3     			0x03		// Display digits 0 and 1 2 3
#define SCAN_LIM4     			0x04		// Display digits 0 and 1 2 3 4
#define SCAN_LIM5     			0x05		// Display digits 0 and 1 2 3 4 5
#define SCAN_LIM6     			0x06		// Display digits 0 and 1 2 3 4 5 6
#define SCAN_LOW_NIBBLE     SCAN_LIM3
#define SCAN_ALL_DIGITS     0x07 
//
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
#define DECIMAL_POINT       0x80
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips);
void max7219_config(uint8_t chip);
inline void max7219_clear(void);
void max7219_write(uint8_t reg, uint8_t data, uint8_t chip);
void max7219_print(const char* format, ...);
void max7219_display(char text[]);
void max7219_NoOperation(void);
void writeChar(char chr, uint8_t chrPos, int8_t  dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void setDpPos(int8_t dpPos[], char chars[]);
uint8_t getCustomChar(char chrAscii);
inline uint8_t isDigit(char chr);
//------------------------------------------------------------------------------
//							See Max7219 datasheet page 8 (Table 5. Code B Font)
//------------------------------------------------------------------------------
const char customChar[2][7] = 
{
	{  '-',  'E',  'H',  'L',  'P',  ' ', '\0' },
	{ 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, '\0' }  // character code
};   
//------------------------------------------------------------------------------
#endif
