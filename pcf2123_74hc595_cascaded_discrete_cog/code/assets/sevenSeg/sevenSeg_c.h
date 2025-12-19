#ifndef SEVEN_SEGMENT_C
#define	SEVEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "sevenSeg_h.h"
//------------------------------------------------------------------------------
void sevenSeg_init(void)
{
  spi_init();
	
	pinMode(CS1, OUTPUT, PUSH_PULL);
	pinMode(OE,  OUTPUT, PUSH_PULL);
	
	digitalWrite(OE, HIGH);    // OE = 1; 	// disable outputs initially
	sevenSeg_clear();
}
//------------------------------------------------------------------------------
void sevenSeg_clear(void)
{
	sevenSeg_string("    ");
	digitalWrite(OE, LOW);    // OE = 0; // Enable outputs
	shiftReg_latch();
}
//------------------------------------------------------------------------------
void sevenSeg_print(const char* format, ...) 
{
	char str[40];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	// send string to 7 seg
	reverseStr(str);
	sevenSeg_string(str);
	shiftReg_latch();
}
//------------------------------------------------------------------------------
void sevenSeg_string(char text[])
{  
	uint8_t chrPos = 0, chr;
	int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	setDpPos(dpPos, text);
	
  while(*text)
  {
		chr = *text++;
		
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
	uint8_t digit = getDigit(chr, chrPos, dpPos);
	spi_write(~digit);	// charset is for common cathode, thus inversion of byte to conform to common anode
}
//------------------------------------------------------------------------------
//													ascii to 7 segment
//------------------------------------------------------------------------------
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
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
			dpPos[pos] = pos;
		}
		else
				{
					pos++;
				}
  }
}
//------------------------------------------------------------------------------
void reverseStr(char str[]) 
{
  uint8_t i = 0, j = strLen(str) - 1;
	
  while (i < j) 
	{
		char tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
  }
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; //Standard ascii range 32 - 127 for printable chars 
}
//------------------------------------------------------------------------------
uint8_t strLen(char str[])
{
	uint8_t len = 0;
	
	while(*str++)
  {
		len++;
	}
	
	return len;
}
//------------------------------------------------------------------------------
void shiftReg_latch(void)
{
	digitalWrite(CS1, LOW);   // CS1 = 0;
	digitalWrite(CS1, HIGH);	// CS1 = 1;
}
//------------------------------------------------------------------------------
#endif
