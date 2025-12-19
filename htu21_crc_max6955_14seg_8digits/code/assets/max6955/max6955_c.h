#ifndef MAX6955_C
#define	MAX6955_C
//------------------------------------------------------------------------------
#include "max6955_h.h"
//------------------------------------------------------------------------------
void max6955_init(uint8_t noChips)
{
  i2c_init();

  while(noChips)
	{
    max6955_config(--noChips);
	}
}
//------------------------------------------------------------------------------
void max6955_config(uint8_t chip)
{     
  max6955_write(DECODE_MODE_REG, DECODE_ALL, chip);    
  max6955_write(INTESITY_REG, BRIGHTNESS, chip);		// Max brightness     
  max6955_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS, chip);  
  max6955_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
	max6955_write(DIGIT_TYPE_REG, MODE_14_SEG, chip);
}
//------------------------------------------------------------------------------
void max6955_write(uint8_t reg, uint8_t data, uint8_t chpNum)
{
  i2c_start(); 
	
	i2c_write(maxAddr[chpNum]);
  i2c_write(reg); 
  i2c_write(data); 

  i2c_stop();
}
//------------------------------------------------------------------------------
void max6955_displayNumber(long number)
{   
  char strNum[15]; 
  sprintf(strNum, "%6li", number);
	
  max6955_displayText(strNum);
}
//------------------------------------------------------------------------------
void max6955_displayText(char text[])
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
	uint8_t chip = chrPos / 8; // Determine which chip to write to based on character position. Max6955 is an 8 digit driver in 14 segment mode
  uint8_t chrAddr = chrPos % 8; // valid character positions range from 0-7 for each chip
	uint8_t digit = getDigit(chr, chrPos, dpPos);
	
	max6955_write(DISPLAY_REG0 + chrAddr, digit, chip);	// character address is 0-15 for each chip. i.e 0x20, 0x21, 0x22, ... 0x27
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
uint8_t getCustomChar(char chrAscii)
{
	uint8_t i = 0, chrCustom = 0;
  
	while(customChar[i])
	{
		 if(chrAscii == customChar[i])
		 {
		   chrCustom = charCode[i]; break;
		 }
		 i++;
	}	
					
	return chrCustom;			
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif	
