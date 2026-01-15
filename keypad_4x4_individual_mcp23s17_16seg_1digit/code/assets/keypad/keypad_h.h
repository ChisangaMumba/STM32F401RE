#ifndef KEYPAD_H
#define KEYPAD_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../mcp23s17/mcp23s17_c.h"
//------------------------------------------------------------------------------
#define KEYPAD_ADDR				0x42		// mcp23s08 i/o expander for Keypad data
#define	chip1							1
//------------------------------------------------------------------------------
#define COL0							0x10
#define COL1							0x20
#define COL2							0x40
#define COL3							0x80
//------------------------------------------------------------------------------
void   keypad_init(void);
inline uint16_t keypad_read(void);
inline int8_t keypad_scan(void);
int32_t keypad_char(char str[], char chr, char backspace, char enter);
int8_t	getPosChar(char str[], char chr);
void 		clearStr(char str[]);
//------------------------------------------------------------------------------
#endif
