#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
#include "../mcp23s08/mcp23s08_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define DIGIT_ADDR				0x40		// mcp23s08 i/o expander for digit data
#define COLUMN_ADDR				0x42		// mcp23s08 i/o expander for column select
//------------------------------------------------------------------------------
void 		sevenSeg_init(void);
void 		sevenSeg_print(const char* format, ...);
void 		sevenSeg_string(char text[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void		setDpPos(int8_t dpPos[], char chars[]);
inline	uint8_t isPrint(char chr);
void 		serial_digitSend(uint8_t digit, uint8_t chrPos);
//------------------------------------------------------------------------------
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
#endif
