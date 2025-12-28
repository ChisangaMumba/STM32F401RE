#ifndef SEVEN_SEGMENT_C
#define	SEVEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "sevenSeg_h.h"
//------------------------------------------------------------------------------
void sevenSeg_init(void)
{
	pcf8575_init(0x00, 0x00);
	sevenSeg_string("  ");
}
//------------------------------------------------------------------------------
void sevenSeg_print(const char* format, ...) 
{
	char str[30];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	sevenSeg_string(str);
}
//------------------------------------------------------------------------------
void sevenSeg_string(char str[])
{  
	uint8_t chrPos = 0,  digit[10];
	int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	setDpPos(dpPos, str);
	
  while(*str)
  {
		uint8_t chr = *str++;
		
		if(chr != '.' && chr != 194)  // ascii 194 is an extra character created by the degree ° symbol
    {
			digit[chrPos] = getDigit(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		} 
  }

	pcf8575_write(digit[1], digit[0]);
}
//------------------------------------------------------------------------------
//													ascii to 7 segment
//------------------------------------------------------------------------------
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isDigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
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
uint8_t getCustomChar(char chrAscii)
{
	uint8_t chrCode = 0x00; /* space char by default*/
  
	for(uint8_t i = 0; customChar[0][i]; i++)
	{
		if(toUpper(chrAscii) == customChar[0][i])
		{
			chrCode = customChar[1][i]; break;
		}
	}	
					
	return chrCode;			
}
//------------------------------------------------------------------------------
inline char toUpper(char chr)
{	
	return (chr >= 'a' && chr <= 'z') ? (chr - 'a' + 'A') : chr;
}
//------------------------------------------------------------------------------
inline uint8_t isDigit(char chr)
{
	return (chr >= '0' && chr <= '9') ? 1 : 0; //Standard ascii range 32 - 127 for printable chars 
}
//------------------------------------------------------------------------------
#endif
