#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define CS1			PA3
#define OE			PA6		// Outout Enable
//------------------------------------------------------------------------------
void 		sevenSeg_init(void);
void 		sevenSeg_clear(void);
void 		sevenSeg_print(const char* format, ...);
void 		sevenSeg_string(char text[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void		setDpPos(int8_t dpPos[], char chars[]);
void		reverseStr(char text[]);
inline	uint8_t isPrint(char chr);
uint8_t strLen(char str[]);
void 		shiftReg_out(uint8_t data);
void		shiftReg_latch(void);
//------------------------------------------------------------------------------
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
#endif
