#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H
//------------------------------------------------------------------------------
#include "../mcp23s17/mcp23s17_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define DIGIT_ADDR				0x40		// mcp23s08 i/o expander for digit data
//------------------------------------------------------------------------------
void 		sevenSeg_init(void);
void 		sevenSeg_char(char chr);
uint8_t getDigit(char chr);
inline	uint8_t isPrint(char chr);
void 		serial_digitSend(uint8_t digit);
//------------------------------------------------------------------------------
#endif
