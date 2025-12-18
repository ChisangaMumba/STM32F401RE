#ifndef MAX7219_C
#define	MAX7219_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "max7219_h.h"
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips)
{
  spi_init();
  pinMode(CS, OUTPUT, PUSH_PULL);
  digitalWrite(CS, HIGH);   // CS1 = 1 (unselect initially)

  while(noChips)
    max7219_config(--noChips);
}
//------------------------------------------------------------------------------
void max7219_config(uint8_t chip)
{     
  max7219_write(DECODE_MODE_REG, DISABLE_DECODE, chip);    
  max7219_write(INTESITY_REG, BRIGHTNESS, chip);     
  max7219_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS, chip);     
  max7219_write(SHUTDOWN_REG, NORMAL_OPERATION,chip);
	max7219_write(DISPLAY_TEST_REG,DISABLE_TEST_MODE, chip);
}
//------------------------------------------------------------------------------
void max7219_write(uint8_t reg, uint8_t data, uint8_t chip)
{
  digitalWrite(CS, LOW);			// CS = 0; 
  
  spi_write(reg); 
  spi_write(data); 
	while(chip--)
      max7219_NoOperation();	// Used for daisy chained (Cascaded) arrangements
  
  digitalWrite(CS, HIGH);			// CS = 1;
}
//------------------------------------------------------------------------------
void max7219_displayNumber(long number)
{   
  char strNum[15]; 
  sprintf(strNum, "%6li", number);
	
  max7219_displayText(strNum);
}
//------------------------------------------------------------------------------
void max7219_displayText(char text[])
{ 
  uint8_t chrPos = 0, i = 0;	
  int8_t dpPos[18] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  setDpPos(dpPos, text);
	
  while(text[i])
  {   
    uint8_t chr = text[i++];  
    
		if(chr != '.' && chr != 194)		//° is implicitly split into 194 and 176 by the arduino c++ compiler
		{
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		}
  }
}
//----------Passes the data to the adjacent max7219 in the Daisy Chain---------
void max7219_NoOperation(void)
{
  spi_write(NO_OP_REG);
  spi_write(0x00);      // Don't care (Can be any arbitrary 8 bit value)  
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t chip = chrPos / 8; // Determine which chip to write to based on character position
  uint8_t chrAddr = chrPos % 8; // valid character positions range from 0-7 for each chip
	uint8_t digit = getDigit(chr, chrPos, dpPos);
	
	max7219_write(chrAddr + 1, digit, chip); // character address is 1-8 for each chip
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
