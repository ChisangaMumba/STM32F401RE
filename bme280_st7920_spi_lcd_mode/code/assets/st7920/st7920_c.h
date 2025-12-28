#ifndef SED1565_C
#define	SED1565_C
//------------------------------------------------------------------------------
#include "st7920_h.h"
//-----------------------Follow Datasheet instructions--------------------------
void st7920_init(void)
{
	spi_init(); 
	
  pinMode(CS1, OUTPUT, PUSH_PULL);
	digitalWrite(CS1, LOW);   // CS1 = 0; // deselect initially

	st7920_command(display_off);
	st7920_command(0x38);							// Function set: 8-bit, 2-line, 5x8 dots
	st7920_command(0x0C);							// Display ON, cursor OFF
	st7920_command(0x06);							// Entry mode set: Increment
	st7920_command(display_clear);		
	st7920_command(display_on);
}
//------------------------------------------------------------------------------
void st7920_data(uint8_t data)
{
	digitalWrite(CS1, HIGH);  // CS1 = 1;

	spi_write(0xFA);									// Send control byte (Data mode: RS = 1, RW = 0)
	spi_write(data & 0xF0);						// Send higher nibble
  spi_write((data << 4) & 0xF0);		// Send lower nibble

	digitalWrite(CS1, LOW);   // CS1 = 0;
}
//------------------------------------------------------------------------------
void st7920_command(uint8_t command)
{	
	digitalWrite(CS1, HIGH);  // CS1 = 1;

	spi_write(0xF8);										// Send control byte (Command mode: RS = 0, RW = 0)
	spi_write(command & 0xF0);					// Send higher nibble
  spi_write((command << 4) & 0xF0);		// Send lower nibble
	
	digitalWrite(CS1, LOW);   // CS1 = 0;
}
//------------------------------------------------------------------------------
void st7920_print(uint8_t row, uint8_t col, const char* format, ...)
{
	char str[30];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	st7920_string(row, col, str);
}	
//------------------------------------------------------------------------------
void st7920_string(uint8_t row, uint8_t col, char text[])
{
  st7920_command(rowAddr[row] | col); 
  
  while(*text)
  {
		uint8_t chr = *text++;
		
		if(chr == 176)    // ° is implicitly split into 194 and 176 by the c compiler
      chr = 0x27;
		
		st7920_data(chr);
  }
}
//------------------------------------------------------------------------------
#endif
