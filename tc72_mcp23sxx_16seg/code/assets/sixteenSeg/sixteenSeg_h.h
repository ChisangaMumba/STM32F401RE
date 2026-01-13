#ifndef SIXTEEN_SEGMENT_H
#define	SIXTEEN_SEGMENT_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
#include "../mcp23s08/mcp23s08_c.h"
#include "../mcp23s17/mcp23s17_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define DIGIT_ADDR				0x40		// mcp23s08 i/o expander for digit data
#define COLUMN_ADDR				0x42		// mcp23s08 i/o expander for column select
//------------------------------------------------------------------------------
void 		sixteenSeg_init(void);
void 		sixteenSeg_print(const char* format, ...);
void 		sixteenSeg_string(char str[]);
void 		writeChar(char chr, uint8_t chrPos);
uint16_t getDigit(char chr, uint8_t chrPos);
inline	uint8_t isPrint(char chr);
void 		serial_digitSend(uint16_t digit, uint8_t chrPos);
//------------------------------------------------------------------------------
#define DECIMAL_POINT 0x4000
//------------------------------------------------------------------------------
#endif
