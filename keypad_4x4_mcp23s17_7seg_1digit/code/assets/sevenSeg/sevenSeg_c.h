#ifndef SEVEN_SEGMENT_C
#define	SEVEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "sevenSeg_h.h"
//------------------------------------------------------------------------------
void sevenSeg_init(void)
{
	mcp23s17_init();
	
	mcp23s17_write(DIGIT_ADDR, IODIR_A, 0x00);		// PORT_A all outputs
	
	sevenSeg_char(' ');
}
//------------------------------------------------------------------------------
void sevenSeg_char(char chr) 
{
	uint8_t digit = getDigit(chr);
	serial_digitSend(digit);  // charset is for common cathode
}
//------------------------------------------------------------------------------
//													ascii to 7 segment
//------------------------------------------------------------------------------
uint8_t getDigit(char chr)
{
	uint8_t digit = 0;
	
	digit = (isPrint(chr)) ? chars[chr - ' '] : custom_chars[0]; // custom char is ° symbol
					
	return digit;
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; //Standard ascii range 32 - 127 for printable chars 
}
//------------------------------------------------------------------------------
void serial_digitSend(uint8_t digit)
{ 
	mcp23s17_write(DIGIT_ADDR, OLAT_A, digit);  		
}
//------------------------------------------------------------------------------
#endif


