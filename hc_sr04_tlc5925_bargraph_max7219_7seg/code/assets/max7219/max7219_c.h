#ifndef MAX7219_C
#define	MAX7219_C
//------------------------------------------------------------------------------
#include "max7219_h.h"
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips)
{
  spi_init();
  pinMode(CS, OUTPUT, PUSH_PULL, NO_PU_PD);
  digitalWrite(CS, HIGH);   // CS = 1 (unselect initially)

  while(noChips)
		max7219_config(--noChips);
}
//------------------------------------------------------------------------------
void max7219_config(uint8_t chip)
{
	max7219_write(DECODE_MODE_REG, DECODE_ALL, chip);   	// Decode every digit using internal digit/character map 
  max7219_write(INTESITY_REG, BRIGHTNESS, chip);      	// Max brightness
  max7219_write(SCAN_LIMIT_REG, SCAN_LOW_NIBBLE, chip); // Display digits 0 and 1 2 3     
  max7219_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
	max7219_clear();
}
//------------------------------------------------------------------------------
inline void max7219_clear(void)
{
	max7219_display("    ");		// Clear zeroes
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
void max7219_print(const char* format, ...) 
{
	char str[40];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	max7219_display(str);
}
//------------------------------------------------------------------------------
void max7219_display(char text[])
{ 
  uint8_t chrPos = 0, i = 0;	
  int8_t  dpPos[18] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  setDpPos(dpPos, text);
	
  while(text[i])
  {   
    uint8_t chr = text[i++];  
    
		if(chr != '.' && chr != 194)		// ° is implicitly split into 194 and 176 by the arduino c++ compiler
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
	uint8_t chip = chrPos / 8;		// Max7219 is an 8 digit driver
	uint8_t chrAddr = chrPos % 8;	// valid character positions range from 0-7 for each chip
	uint8_t digit = getDigit(chr, chrPos, dpPos);
	
	max7219_write(chrAddr + 1, digit, chip);	// character address is 1-8 for each chip
}
//------------------------------------------------------------------------------
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = 0;
	
	digit = (isDigit(chr)) ? chr - '0' : getCustomChar(chr);
					
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
	uint8_t chrCode = 0x0F; /* space char by default*/
  
	for(uint8_t i = 0; customChar[0][i]; i++)
	{
		if(chrAscii == customChar[0][i])
		{
			chrCode = customChar[1][i]; break;
		}
	}	
					
	return chrCode;			
}
//------------------------------------------------------------------------------
inline uint8_t isDigit(char chr)
{
	return (chr >= '0' && chr <= '9') ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif	
