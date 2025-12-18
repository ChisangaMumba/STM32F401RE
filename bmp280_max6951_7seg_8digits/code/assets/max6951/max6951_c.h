#ifndef MAX6951_C
#define	MAX6951_C
//------------------------------------------------------------------------------
#include "max6951_h.h"
//------------------------------------------------------------------------------
void max6951_init(uint8_t noChips)
{
  spi_init();

  while(noChips)
	{
		pinMode(chips[--noChips], OUTPUT, PUSH_PULL);
		digitalWrite(chips[noChips], HIGH);   // CS = 1 (unselect initially)
    max6951_config(noChips);
	}
}
//------------------------------------------------------------------------------
void max6951_config(uint8_t chip)
{     
  max6951_write(DECODE_MODE_REG, DISABLE_DECODE, chip);    
  max6951_write(INTESITY_REG, BRIGHTNESS, chip);		// Max brightness     
  max6951_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS, chip);	  
  max6951_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void max6951_write(uint8_t reg, uint8_t data, uint8_t chpNum)
{
  digitalWrite(chips[chpNum], LOW);		// CS = 0; 
	
  spi_write(reg); 
  spi_write(data); 

  digitalWrite(chips[chpNum], HIGH);	// CS = 1;
}
//------------------------------------------------------------------------------
void max6951_displayNumber(long number)
{   
  char strNum[15]; 
  sprintf(strNum, "%6li", number);
	
  max6951_displayText(strNum);
}
//------------------------------------------------------------------------------
void max6951_displayText(char text[])
{ 
  uint8_t chrPos = 0;	
  int8_t  dpPos[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  setDpPos(dpPos, text);
	
  while(*text)
  {   
    uint8_t chr = *text++;  
    
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
	uint8_t chip = chrPos / 8; // Determine which chip to write to based on character position. Max6951 is a 8 digit driver
  uint8_t chrAddr = chrPos % 8; // valid character positions range from 0-7 for each chip
	uint8_t digit = getDigit(chr, chrPos, dpPos);
	
	max6951_write(DISPLAY_REG0 + chrAddr, digit, chip);	// character address is 0-7 for each chip. i.e 0x20, 0x21, 0x22,... 0x27
}
//------------------------------------------------------------------------------
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isPrint(chr)) ? chars[chr - ' '] : custom_chars[0];
					
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
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif	
