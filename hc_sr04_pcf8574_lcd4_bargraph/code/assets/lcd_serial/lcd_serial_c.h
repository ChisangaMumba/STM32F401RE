#ifndef LCD8_C
#define	LCD8_C
//------------------------------------------------------------------------------
#include "lcd_serial_h.h"
//-----------------------Follow Datasheet instructions--------------------------
void lcd_init(void)
{
  i2c_init();    
  pcf8574_init(0x00); // Initialize PCF8574 with all pins low (outputs)

  lcd_command(home);
  lcd_command(function_set4);   
  lcd_command(display_on);      
  lcd_command(auto_increment);
	
	lcd_createChar(0, customChrs[0]);
	lcd_createChar(1, customChrs[1]);
	lcd_createChar(2, customChrs[2]);
	lcd_createChar(3, customChrs[3]);
	lcd_createChar(4, customChrs[4]);
	lcd_createChar(5, customChrs[5]);
}
//------------------------------------------------------------------------------
void lcd_command(uint8_t command)
{
  RS = 0;     //  Instruction register ( commands ).
  lcd_sendBits(command);
}
//------------------------------------------------------------------------------
void lcd_data(uint8_t data)
{
  RS = 1;     //  Data register  ( strings and characters ).
  lcd_sendBits(data);
}
//------------------------------------------------------------------------------
void lcd_print(uint8_t row, uint8_t col, const char* format, ...) 
{
	char str[40];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	lcd_string(row, col, str);
}
//------------------------------------------------------------------------------
void lcd_string(uint8_t row, uint8_t column, char text[])
{
	lcd_setPos(row, column);  // Set coordinates.

  while(*text)				// null terminator.
  {
    uint8_t chr = *text++;
		
		if(chr == 176)    // 176 is ° in Extended ascii
			chr = 0xDF;     // 223d is the value of ° symbol in Hitachi HD44780 lcds
		
		if(chr != 194)	  // ° is implicitly split into 194 and 176 by the arduino c++ compiler
      lcd_data(chr);  // Increment pointer to next character.
  }
}
//------------------------------------------------------------------------------
void lcd_sendBits(uint8_t data)
{
	lcd_sendNibble(data & 0xF0);     // Higher Nibble
  lcd_sendNibble(data << 4);       // Lower Nibble
}
//------------------------------------------------------------------------------
void lcd_setPos(uint8_t row, uint8_t column)
{
	lcd_command(rowAddr[row] + column);  // Set coordinates.
}
//------------------------------------------------------------------------------
void lcd_sendNibble(uint8_t data)
{
  data = data | RS;
	
  // Enable is pulsed to latch the data
  pcf8574_write(data | EN_high);
  delay_us(5);
  pcf8574_write(data & EN_low);
}
//------------------------------------------------------------------------------
void lcd_createChar(uint8_t reg, const uint8_t data[])
{
	uint8_t i;
	
	if(reg < 8)					// valid addresses range from 0 - 7
	{
		lcd_command(CGRAM + (reg * 8));  // write to CGRAM
		
		for(i = 0; i < 8; i++)
			lcd_data(data[i]);
	}
	
	lcd_command(DDRAM);	// Shift back to DDRAM location 0
}
//------------------------------------------------------------------------------
void lcd_bargraph(uint8_t row, uint16_t input, uint16_t inputMax)
{
	float factor = inputMax / 80.0f;	// 16 character max on 16 x 2 lcd. Each char has 5 sections therefore 16 x 5 = 80.
	int16_t percent = (input + 1) / factor;
	int16_t colNum = percent / 5;
	int16_t remainder = percent % 5;
	
	if(colNum > 0)
	{
		for(uint16_t col = 0; col < colNum; col++)
		{
			lcd_setPos(row, col);
			lcd_data(5);
		}
	}

	lcd_setPos(row, colNum);
	lcd_data(remainder); 
	
	if(colNum < 16)
	{
		for(uint16_t col = colNum + 1; col <= 16; col++)
		{
			lcd_setPos(row, col);
			lcd_data(0);
		}
	} 
}
//------------------------------------------------------------------------------
#endif
