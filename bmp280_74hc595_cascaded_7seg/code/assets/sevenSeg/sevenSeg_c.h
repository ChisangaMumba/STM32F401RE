#ifndef SEVEN_SEGMENT_C
#define	SEVEN_SEGMENT_C
//------------------------------------------------------------------------------
#include "sevenSeg_h.h"
//------------------------------------------------------------------------------
void sevenSeg_init(void)
{
  spi_init();
	
	pinMode(CS1, OUTPUT, PUSH_PULL);
	
	//de-select Shift Registers initially
	digitalWrite(CS1, HIGH);    // CS1 = 1;
	sevenSeg_clear();
}
//------------------------------------------------------------------------------
inline void sevenSeg_clear(void)
{
	sevenSeg_string("        ");
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
	
	sevenSeg_string(str);
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
	shiftReg_digitSend(~digit, chrPos);  // charset is for common cathode, thus inversion of byte to conform to common anode
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
void shiftReg_digitSend(uint8_t digit, uint8_t chrPos)
{ 
	// Fist-in First-out
	spi_write(0x01 << chrPos); // select column from second shift register
	spi_write(digit);  				 // write digit to first shift register
	
	shiftReg_latch();
}
//------------------------------------------------------------------------------
void shiftReg_latch(void)
{
	digitalWrite(CS1, LOW);   // CS1 = 0;
	delay_us(1);
	digitalWrite(CS1, HIGH);	// CS1 = 1;
	delay_us(1);
}
//------------------------------------------------------------------------------
#endif
