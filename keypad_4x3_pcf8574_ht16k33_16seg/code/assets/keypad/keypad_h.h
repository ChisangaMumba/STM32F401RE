#ifndef KEYPAD4x3_H
#define KEYPAD4x3_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../pcf8574/pcf8574_c.h"
//------------------------------------------------------------------------------
#define KEYPAD_ADDR				0x40		// mcp23s08 i/o expander for Keypad data
//------------------------------------------------------------------------------
#define COL0							0x10
#define COL1							0x20
#define COL2							0x40
#define COL3							0x80
//------------------------------------------------------------------------------
void   keypad_init(void);
inline void keypad_rowSelect(uint8_t data);
inline int8_t keypad_scan(void); 
int32_t keypad_char(char str[], char chr, char backspace, char enter);
int8_t	getPosChar(char str[], char chr);
void 		clearStr(char str[]);
//------------------------------------------------------------------------------
uint8_t indices[4][3] = 
{
// columns
// 0   1	 2
	{0,  1,  2},  // Row 0
	{3,  4,  5},	// Row 1
	{6,  7,  8},	// Row 2 
	{9, 10, 11},	// Row 3
};
//------------------------------------------------------------------------------
#endif
