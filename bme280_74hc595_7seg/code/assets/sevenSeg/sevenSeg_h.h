#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define CS1			PA3
#define CS2			PA4
//------------------------------------------------------------------------------
void 		sevenSeg_init(void);
void		sevenSeg_integer(int32_t number);
void 		sevenSeg_string(char text[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void		setDpPos(int8_t dpPos[], char chars[]);
inline	uint8_t isPrint(char chr);
void 		shiftReg_digitSend(uint8_t digit, uint8_t chrPos);
void 		shiftReg_colSend(uint8_t col);
void 		shiftReg_colSelect(uint8_t pos);
//------------------------------------------------------------------------------
#define DECIMAL_POINT 0x80
//-------------------------------Common Anode-----------------------------------
//															0 , 1  ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,  9
//const uint8_t digits[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; 
//------------------------------------------------------------------------------
#endif
