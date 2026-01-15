#ifndef SIXTEEN_SEGMENT_C
#define	SIXTEEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "sixteenSeg_h.h"
//------------------------------------------------------------------------------
void sixteenSeg_init(void)
{
	pcf8575_init(DIGIT_ADDR, 0x00, 0x00);
	
	sixteenSeg_char(' ');
}
//------------------------------------------------------------------------------
void sixteenSeg_char(char chr) 
{
	uint16_t digit = getDigit(chr);
	serial_digitSend(digit);  // charset is for common anode, thus inversion of byte to conform to common cathode
}
//------------------------------------------------------------------------------
//													ascii to 16 segment
//------------------------------------------------------------------------------
uint16_t getDigit(char chr)
{
	uint16_t digit = 0;
	
	digit = (isPrint(chr)) ? chars[chr - ' '] : custom_chars[0]; // custom char is ° symbol
					
	return digit;
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; //Standard ascii range 32 - 127 for printable chars 
}
//------------------------------------------------------------------------------
void serial_digitSend(uint16_t digit)
{ 
	pcf8575_write(DIGIT_ADDR, digit, digit >> 8);  			// MSByte,  LSByte	
}
//------------------------------------------------------------------------------
#endif
