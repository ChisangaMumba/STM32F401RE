#ifndef SIXTEEN_SEGMENT_H
#define	SIXTEEN_SEGMENT_H
//------------------------------------------------------------------------------
#include "../pcf8575/pcf8575_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define DIGIT_ADDR				0x40		// mcp23s08 i/o expander for digit data
//------------------------------------------------------------------------------
void 		sixteenSeg_init(void);
void 		sixteenSeg_char(char chr);
uint16_t getDigit(char chr);
inline	uint8_t isPrint(char chr);
void 		serial_digitSend(uint16_t digit);
//------------------------------------------------------------------------------
#endif
