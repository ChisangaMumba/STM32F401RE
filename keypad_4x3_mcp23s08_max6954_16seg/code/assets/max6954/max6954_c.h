#ifndef MAX6954_C
#define	MAX6954_C
//------------------------------------------------------------------------------
#include "max6954_h.h"
//------------------------------------------------------------------------------
void max6954_init(uint8_t noChips)
{
  spi_init(1);		// SPI1 selected

  while(noChips)
	{
		pinMode(chips[--noChips], OUTPUT, PUSH_PULL, NO_PU_PD);
		digitalWrite(chips[noChips], HIGH);   // CS = 1 (unselect initially)
    max6954_config(noChips);
	}
}
//------------------------------------------------------------------------------
void max6954_config(uint8_t chip)
{     
  max6954_write(DECODE_MODE_REG, DECODE_ALL, chip);    
  max6954_write(INTESITY_REG, BRIGHTNESS, chip);		// Max brightness     
  max6954_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS, chip);  
  max6954_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void max6954_write(uint8_t reg, uint8_t data, uint8_t chpNum)
{
  digitalWrite(chips[chpNum], LOW);		// CS = 0; 
	
  spi_write(reg); 
  spi_write(data); 

  digitalWrite(chips[chpNum], HIGH);	// CS = 1;
}
//------------------------------------------------------------------------------
void max6954_print(const char* format, ...)
{   
  char str[40]; 
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
  max6954_string(str);
}
//------------------------------------------------------------------------------
void max6954_string(char str[])
{ 
  uint8_t chrPos = 0;	
  int8_t  dpPos[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  setDpPos(dpPos, str);
	
  while(*str)
  {   
    uint8_t chr = *str++;  
    
		if(chr != '.' && chr != 194)		//° is implicitly split into 194 and 176 by the arduino c++ compiler
		{
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		}
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t chip = chrPos / 8; // Determine which chip to write to based on character position. Max6954 is a 8 digit driver in 16 segment mode
  uint8_t chrAddr = chrPos % 8; // valid character positions range from 0-7 for each chip
	uint8_t digit = getDigit(chr, chrPos, dpPos);
	
	max6954_write(DISPLAY_REG0 + chrAddr, digit, chip);	// character address is 0-15 for each chip. i.e 0x20, 0x21, 0x22, ... 0x27
}
//------------------------------------------------------------------------------
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isPrint(chr)) ? chr : getCustomChar(chr);
					
	return (dpPos != -1 && chrPos == dpPos) ? digit + DECIMAL_POINT  : digit;
}
//------------------------------------------------------------------------------
void setDpPos(int8_t dpPos[], char chars[])
{
  uint8_t pos = 0; 
	
  for(uint8_t i = 0; chars[i]; i++)
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
uint8_t getCustomChar(char chr)
{	
	uint8_t col = 0, chrCustom = 0;
	
	while(customChar[0][col])
	{
		 if(chr == customChar[0][col])						// Character, ROW 0
		 {
		   chrCustom = customChar[1][col]; break;	// Character Code, ROW 1 
		 }
		 col++;
	}	
					
	return chrCustom;	
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;  // valide range of standard printable ascii characters
}
//------------------------------------------------------------------------------
#endif	
