#ifndef FOURTEEN_SEGMENT_H
#define	FOURTEEN_SEGMENT_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../pca9554/pca9554_c.h"
#include "../pca9555/pca9555_c.h"
#include "charset.h"
//--------------------------------------------------------------------------
#define DIGIT_ADDR				0x40		// mcp23008 i/o expander for digit data
#define COLUMN_ADDR				0x42		// mcp23008 i/o expander for column select
//------------------------------------------------------------------------------
void 		fourteenSeg_init(void);
void 		fourteenSeg_print(const char* format, ...);
void 		fourteenSeg_string(char str[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t dpPos);
void		serial_digitSend(uint16_t digit, uint8_t colSelect);
uint16_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void		setDpPos(int8_t dpPos[], char chars[]);
inline	uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
#define DECIMAL_POINT 0x4000
//------------------------------------------------------------------------------
#endif
