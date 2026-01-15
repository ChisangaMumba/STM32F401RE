#ifndef SIXTEEN_SEGMENT_H
#define	SIXTEEN_SEGMENT_H
//------------------------------------------------------------------------------
#include "../mcp23s17/mcp23s17_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define DIGIT_ADDR				0x40		// mcp23s08 i/o expander for digit data
#define	chip0							0
//------------------------------------------------------------------------------
void 		sixteenSeg_init(void);
void 		sixteenSeg_char(char chr);
uint16_t getDigit(char chr);
inline	uint8_t isPrint(char chr);
void 		serial_digitSend(uint16_t digit);
//------------------------------------------------------------------------------
#endif
