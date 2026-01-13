#ifndef SIXTEEN_SEGMENT_C
#define	SIXTEEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "sixteenSeg_h.h"
//------------------------------------------------------------------------------
void sixteenSeg_init(void)
{
	mcp23017_init(DIGIT_ADDR, 0x00, 0x00);
	mcp23008_init(COLUMN_ADDR, 0x00);
	
	sixteenSeg_string("         ");
}
//------------------------------------------------------------------------------
void sixteenSeg_print(const char* format, ...) 
{
	char str[40];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	sixteenSeg_string(str);
}
//------------------------------------------------------------------------------
void sixteenSeg_string(char str[])
{  
	uint8_t chrPos = 0;
	
  while(*str)
  {
		writeChar(*str++, chrPos++); 
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos)
{
	uint16_t digit = getDigit(chr, chrPos);
	serial_digitSend(digit, chrPos);  // charset is for common anode, thus inversion of byte to conform to common cathode
}
//------------------------------------------------------------------------------
//													ascii to 16 segment
//------------------------------------------------------------------------------
uint16_t getDigit(char chr, uint8_t chrPos)
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
void serial_digitSend(uint16_t digit, uint8_t chrPos)
{ 
	mcp23017_write(DIGIT_ADDR, OLAT_A, digit);  			// LSByte
	mcp23017_write(DIGIT_ADDR, OLAT_B, digit >> 8);		// MSByte
	delay_us(820);
	mcp23008_write(COLUMN_ADDR, OLAT, ~(0x01 << chrPos));
}
//------------------------------------------------------------------------------
#endif
