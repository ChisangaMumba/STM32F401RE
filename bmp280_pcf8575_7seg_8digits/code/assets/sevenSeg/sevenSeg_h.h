#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../pcf8575/pcf8575_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
void 		sevenSeg_init(void);
void 		sevenSeg_print(const char* format, ...);
void 		sevenSeg_string(char text[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void		setDpPos(int8_t dpPos[], char chars[]);
inline	uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
#endif
