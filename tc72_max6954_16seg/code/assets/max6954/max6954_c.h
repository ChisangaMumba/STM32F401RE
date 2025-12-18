#ifndef MAX6954_C
#define	MAX6954_C
//------------------------------------------------------------------------------
#include "max6954_h.h"
//------------------------------------------------------------------------------
void max6954_init(void)
{
  spi_init();
  pinMode(CS, OUTPUT, PUSH_PULL);
     
  max6954_write(DECODE_MODE_REG, DECODE_ALL);	// Decode ascii characters    
  max6954_write(INTESITY_REG, BRIGHTNESS);     
  max6954_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS);     
  max6954_write(SHUTDOWN_REG, NORMAL_OPERATION);
}
//------------------------------------------------------------------------------
void max6954_write(uint8_t reg, uint8_t data)
{
  digitalWrite(CS, LOW);		// CS = 0; 
  
  spi_write(reg); 
  spi_write(data); 
  
  digitalWrite(CS, HIGH);		// CS = 1;
}
//------------------------------------------------------------------------------
void max6954_displayNumber(long number)
{   
  char strNum[15]; 
  sprintf(strNum, "%6li", number);
	
  max6954_displayText(strNum);
}
//------------------------------------------------------------------------------
void max6954_displayText(char text[])
{ 
  uint8_t chrPos = 0;	
  int8_t  dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  setDpPos(dpPos, text);
	
  while(*text)
  {   
    uint8_t chr = *text++;  
    
		if(chr != '.' && chr != 194) // ° is implicitly split into 194 and 176 by the arduino c++ compiler
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
	max6954_write(DISPLAY_REG0 + chrPos, digit);
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
