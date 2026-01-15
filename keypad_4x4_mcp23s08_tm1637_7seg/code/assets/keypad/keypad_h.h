#ifndef KEYPAD_H
#define KEYPAD_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../mcp23s08/mcp23s08_c.h"
//------------------------------------------------------------------------------
#define KEYPAD_ADDR				0x42		// mcp23s08 i/o expander for Keypad data
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
uint8_t indices[4][4] = 
{
// 			columns
//   0   1	 2   3
	{  0,  1,  2,  3 }, // Row 0
	{  4,  5,  6,  7 },	// Row 1
	{  8,  9, 10, 11 },	// Row 2 
	{ 12, 13, 14, 15 },	// Row 3
};
//------------------------------------------------------------------------------
#endif
