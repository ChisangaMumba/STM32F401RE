#ifndef MAX6952_C
#define	MAX6952_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "max6952_h.h"
//------------------------------------------------------------------------------
void max6952_init(uint8_t noChips)
{
  spi_init();
  pinMode(CS, OUTPUT, PUSH_PULL);
     
  while(noChips)
     max6952_config(--noChips);
}
//------------------------------------------------------------------------------
void max6952_config(uint8_t chip)
{
  max6952_write(DECODE_MODE_REG, DECODE_ALL, chip); // Decodes ascii characters    
  max6952_write(INTESITY_REG10, BRIGHTNESS, chip); 
	max6952_write(INTESITY_REG32, BRIGHTNESS, chip);
  max6952_write(SCAN_LIMIT_REG, SCAN_LOW_NIBBLE, chip);     
  max6952_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void max6952_write(uint8_t reg, uint8_t data, uint8_t chip)
{
  digitalWrite(CS, LOW);		// CS = 0; 
  
  spi_write(reg); 
  spi_write(data);
	while(chip--)
		max6952_NoOperation();  // Used for daisy chained (Cascaded) arrangements
  
  digitalWrite(CS, HIGH);		// CS = 1;
}
//------------------------------------------------------------------------------
void max6952_displayNumber(long number)
{   
  char strNum[15]; 
  sprintf(strNum, "%6li", number);
	
  max6952_displayText(strNum);
}
//------------------------------------------------------------------------------
void max6952_displayText(char text[])
{ 
	uint8_t chrPos = 0;
	
  while(*text)
  {   
		writeChar(*text++, chrPos++);
  }
}
//-----------Passes the data to the adjacent max6952 in the Daisy Chain---------
void max6952_NoOperation(void)
{
  spi_write(NO_OP_REG);           
  spi_write(0x00);                // Don't care (Can be any arbitrary value)
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos)
{
	uint8_t chip = chrPos / 4;			// Determine which chip to write to based on character position. Max6952 is a 4 digit driver
  uint8_t chrAddr = chrPos % 4; 	// valid character positions range from 0-3 for each chip
	uint8_t digit = getDigit(chr);
	
	max6952_write(DISPLAY_REG0 + chrAddr, digit, chip);	// character address is 0-3 for each chip. i.e 0x20, 0x21, 0x22, 0x23
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
