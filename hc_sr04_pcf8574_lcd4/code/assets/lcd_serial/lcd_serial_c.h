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
void lcd_string(uint8_t row, uint8_t column, char text[])
{
  lcd_command(rowAddr[row] + column);  // Set coordinates.

  while(*text)  // Loop until null terminator.
  {
    uint8_t chr = *text++;
		
		if(chr == 176)    // 176 is ° in Extended ascii
			chr = 0xDF;     //223d is the value of ° symbol in Hitachi HD44780 lcds
		
		if(chr != 194)	  //° is implicitly split into 194 and 176 by the arduino c++ compiler
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
void lcd_sendNibble(uint8_t data)
{
  data = data | RS;
	
  // Enable is pulsed to latch the data
  pcf8574_write(data | EN_high);
  delay_us(500);
  pcf8574_write(data & EN_low);
}
//------------------------------------------------------------------------------
#endif
