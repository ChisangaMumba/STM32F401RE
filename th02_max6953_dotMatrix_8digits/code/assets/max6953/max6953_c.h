#ifndef MAX6953_C
#define	MAX6953_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "max6953_h.h"
//------------------------------------------------------------------------------
void max6953_init(uint8_t noChips)
{	
  i2c_init();
     
  while(noChips)
     max6953_config(--noChips);
}
//------------------------------------------------------------------------------
void max6953_config(uint8_t chip)
{
  max6953_write(DECODE_MODE_REG, DECODE_ALL, chip); // Decodes ascii characters    
  max6953_write(INTESITY_REG10, BRIGHTNESS, chip); 
	max6953_write(INTESITY_REG32, BRIGHTNESS, chip);
  max6953_write(SCAN_LIMIT_REG, SCAN_LOW_NIBBLE, chip);     
  max6953_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void max6953_write(uint8_t reg, uint8_t data, uint8_t chip)
{	
	i2c_start();
  
	i2c_write(maxAddr[chip]);
  i2c_write(reg); 
  i2c_write(data);

  i2c_stop();
}
//------------------------------------------------------------------------------
void max6953_displayNumber(long number)
{   
  char strNum[15]; 
  sprintf(strNum, "%6li", number);
	
  max6953_displayText(strNum);
}
//------------------------------------------------------------------------------
void max6953_displayText(char text[])
{ 
	uint8_t chrPos = 0;
	
  while(*text)
  {   
		writeChar(*text++, chrPos++);
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos)
{
	uint8_t chip = chrPos / 4;			// Determine which chip to write to based on character position. Max6953 is a 4 digit driver
  uint8_t chrAddr = chrPos % 4; 	// valid character positions range from 0-3 for each chip
	uint8_t digit = getDigit(chr);
	
	max6953_write(DISPLAY_REG0 + chrAddr, digit, chip);	// character address is 0-3 for each chip. i.e 0x20, 0x21, 0x22, 0x23
}
//------------------------------------------------------------------------------
uint8_t getDigit(char chr)
{
	uint8_t digit = 0;
	
	digit = (isPrint(chr)) ? chr : getCustomChar(chr);
					
	return digit;
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
