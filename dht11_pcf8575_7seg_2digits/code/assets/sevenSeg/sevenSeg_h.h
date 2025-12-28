#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../pcf8575/pcf8575_c.h"
//------------------------------------------------------------------------------
void 		sevenSeg_init(void);
void 		sevenSeg_print(const char* format, ...);
void 		sevenSeg_string(char str[]);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void		setDpPos(int8_t dpPos[], char chars[]);
uint8_t getCustomChar(char chrAscii);
inline	char toUpper(char chr);
inline	uint8_t isDigit(char chr);
//------------------------------------------------------------------------------
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
//Common Anode					 0,    1,    2,    3,    4,    5,    6,    7,    8,   9
//------------------------------------------------------------------------------
const char digits[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 };
//----------------------------Custom characters---------------------------------
const char customChar[2][10] = 
{
	{  '-',  ' ',  '°',  'C',  'F',  '%',  'E',  'O',  'R', '\0' },
	{ 0xDF, 0xFF, 0x9C, 0xD1, 0xD8, 0x98, 0xD0, 0xE4, 0xFA, '\0' }  // character code
};
//------------------------------------------------------------------------------
#endif
