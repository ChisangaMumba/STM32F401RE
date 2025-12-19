#ifndef LCD_SERIAL_C
#define LCD_SERIAL_C
//------------------------------------------------------------------------------
#include "lcd_serial_h.h"
//--------------------------------JHD1214---------------------------------------
void lcd_init(void)
{
  delay_ms(30);    // Wait for more than 30ms after Vdd rises to 4.5v           	
  i2c_init();     
  
  i2c_start();
	
  i2c_write(DEV_ADDR);             
  delay_ms(50);
  lcd_command(home);
  lcd_command(function_set4);
  lcd_command(font2a);
  lcd_command(display_on);
  lcd_command(clear); 
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void lcd_command(uint8_t data)
{
	i2c_write(CMD_REG);		// C0 = 1 RS = 0 (Instruction Register ( commands ))
	i2c_write(data);
}
//------------------------------------------------------------------------------
void lcd_setPos(uint8_t data)
{
	i2c_start();              
	i2c_write(DEV_ADDR); 
	
    lcd_command(data);  
	
	i2c_stop();
}
//------------------------------------------------------------------------------
void lcd_string(uint8_t row, uint8_t col, char text[])
{
	lcd_setPos(RowAddr[row] + col);
	
	i2c_start(); 
	
	i2c_write(DEV_ADDR); 
	i2c_write(DAT_REG);		// C0 = 0 RS = 0 Data Register (Strings and characters).	
	while(*text)
	{
		uint8_t chr = *text++;
		
		if(chr == 176)    	// 176 is ° in Extended ascii
			chr = 0xDF;   		// 223d is the value of ° symbol in Hitachi HD44780 lcds
		
		if(chr != 194)	  	// ° is implicitly split into 194 and 176 by the arduino c++ compiler
			i2c_write(chr);
		
	}
	
	i2c_stop();
}
//------------------------------------------------------------------------------
#endif
