#ifndef FOURTEEN_SEGMENT_C
#define	FOURTEEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "fourteenSeg_h.h"
//------------------------------------------------------------------------------
void fourteenSeg_init(void)
{
	pca9555_init(DIGIT_ADDR, 0x00, 0x00);
	pca9554_init(COLUMN_ADDR, 0x00);
	fourteenSeg_string("         ");
}
//------------------------------------------------------------------------------
void fourteenSeg_print(const char* format, ...) 
{
	char str[30];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	fourteenSeg_string(str);
}
//------------------------------------------------------------------------------
void fourteenSeg_string(char str[])
{  
	uint8_t chrPos = 0;
	int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	setDpPos(dpPos, str);
	
  while(*str)
  {
		uint8_t chr = *str++;
	
		if(chr != '.' && chr != 194)  // ascii 194 is an extra character created by the degree ° symbol
    {
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		} 
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint16_t digit = getDigit(chr, chrPos, dpPos);
	uint8_t colSelect = ~(0x01 << chrPos);		
	
	serial_digitSend(digit, colSelect);
}
//------------------------------------------------------------------------------
void serial_digitSend(uint16_t digit, uint8_t colSelect)
{ 
	pca9555_write8(DIGIT_ADDR, PORTA_WR, digit);
	pca9555_write8(DIGIT_ADDR, PORTB_WR, digit >> 8);
	delay_ms(3);
	pca9554_write(COLUMN_ADDR, PORT_OUT_REG, colSelect);
}
//------------------------------------------------------------------------------
//													ascii to 14 segment
//------------------------------------------------------------------------------
uint16_t getDigit(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint16_t digit = 0;
	
	digit = (isPrint(chr)) ? chars[chr - ' '] : custom_chars[0]; // custom char is ° symbol
					
	return (dpPos != -1 && chrPos == dpPos) ? (digit + DECIMAL_POINT)  : digit;
}
//------------------------------------------------------------------------------
void setDpPos(int8_t dpPos[], char chars[])
{
	uint8_t i, pos = 0; 
	
	for(i = 0; chars[i]; i++)
  {
    if(chars[i] == '.')
		{
			dpPos[pos-1] = pos - 1;
		}
		else
				{
					pos++;
				}
  }
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; //Standard ascii range 32 - 127 for printable chars 
}
//------------------------------------------------------------------------------
#endif
