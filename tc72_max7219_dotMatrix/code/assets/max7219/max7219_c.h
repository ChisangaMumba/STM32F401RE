#ifndef MAX7219_C
#define	MAX7219_C
//------------------------Dot Matrix LED  Driver--------------------------------
#include "max7219_h.h"
//------------------------------------------------------------------------------
void max7219_init(uint8_t noChips)
{
  spi_init();
  pinMode(CS, OUTPUT, PUSH_PULL);
     
  while(noChips)
     max7219_config(--noChips);
}
//------------------------------------------------------------------------------
void max7219_config(uint8_t chip)
{
  max7219_write(DECODE_MODE_REG, DISABLE_DECODE, chip);    
  max7219_write(INTESITY_REG, BRIGHTNESS, chip);     
  max7219_write(SCAN_LIMIT_REG, SCAN_ALL_DIGITS, chip);     
  max7219_write(SHUTDOWN_REG, NORMAL_OPERATION, chip);
}
//------------------------------------------------------------------------------
void max7219_write(uint8_t reg, uint8_t data, uint8_t chip)
{
  digitalWrite(CS, LOW);		// CS = 0; 
  
  spi_write(reg); 
  spi_write(data);
	while(chip--)
		max7219_NoOperation();  // Used for daisy chained (Cascaded) arrangements
  
  digitalWrite(CS, HIGH);		// CS = 1;
}
//------------------------------------------------------------------------------
void max7219_displayNumber(long number)
{   
  char strNum[15]; 
  sprintf(strNum, "%5li", number);
	
  max7219_displayText(strNum);
}
//------------------------------------------------------------------------------
void max7219_displayText(char text[])
{ 
  uint8_t chip = 0;	
	
  while(*text)
  {   
    uint8_t chr = *text++;  
    
		writeChar(chr, chip);
		
		if(isPrint(chr) && chr != '.' && (chr != 176 || chr != 194))
		{
			chip++;
		}
  }
}
//-----------Passes the data to the adjacent max7219 in the Daisy Chain---------
void max7219_NoOperation(void)
{
  spi_write(NO_OP_REG);           
  spi_write(0x00);                // Don't care (Can be any arbitrary value)
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr, uint8_t chip)
{
	uint8_t row, col; 

  for(col = 0; col < 5; col++)
  {
    if(isPrint(chr) && chr != '.' && chr != 194) // If the character is printable and not a decimal point or degree symbol
    {
      row = chr - ' ';
			max7219_write(col+1, chars[row][col], chip);
    }
    else
        if(chr == 176) // If the character is a degree symbol (°)
        {
          // ° is implicitly split into 194 and 176 by the arduino c++ compiler
					max7219_write(7, custom_chars[0][3], chip-1);
          max7219_write(8, custom_chars[0][4], chip-1);
        }
  }

  displayDp(chr, chip);   // Display decimal point if needed
}
//------------------------------------------------------------------------------
void displayDp(uint8_t chr, uint8_t chip)
{
  if(chr == '.')
  { 
		max7219_write(7, 0x60, chip-1);
    max7219_write(8, 0x60, chip-1);
  }
}
//------------------------------------------------------------------------------
uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif	
