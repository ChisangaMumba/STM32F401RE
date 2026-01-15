#ifndef SIXTEEN_SEGMENT_C
#define	SIXTEEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "sixteenSeg_h.h"
//------------------------------------------------------------------------------
void sixteenSeg_init(void)
{
	mcp23s17_init(DIGIT_ADDR, chip0);
	mcp23s17_write(DIGIT_ADDR, IODIR_A, 0x00, chip0);		// PORT-A all outputs
	mcp23s17_write(DIGIT_ADDR, IODIR_B, 0x00, chip0);		// PORT-B all outputs
	
	sixteenSeg_char(' ');
}
//------------------------------------------------------------------------------
void sixteenSeg_char(char chr) 
{
	uint16_t digit = getDigit(chr);
	serial_digitSend(digit);  // charset is for common cathode (invert byte to conform to common anode)
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
	mcp23s17_write(DIGIT_ADDR, OLAT_A, digit, chip0);  				// LSByte
	mcp23s17_write(DIGIT_ADDR, OLAT_B, digit >> 8, chip0);		// MSByte
}
//------------------------------------------------------------------------------
#endif
