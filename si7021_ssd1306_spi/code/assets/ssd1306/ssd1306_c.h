#ifndef SSD1306_C
#define SSD1306_C
//------------------------------------------------------------------------------
#include "ssd1306_h.h"
//------------------------------------------------------------------------------
void ssd1306_init(void) 
{
  spi_init();
  pinMode(CS1, OUTPUT, PUSH_PULL);
	pinMode(DC, OUTPUT, PUSH_PULL);
	pinMode(RST, OUTPUT, PUSH_PULL);
	
	digitalWrite(CS1, HIGH);		// CS1 = 1; // deselect initially
	ssd1306_reset();
	
	ssd1306_command(SSD1306_DISPLAY_OFF); // Display off
	ssd1306_command(0xD5); // Set display clock divide ratio
	ssd1306_command(0x80); // Suggested ratio
	ssd1306_command(0xA8); // Set multiplex ratio
	ssd1306_command(0x3F); // 1/64 duty
	ssd1306_command(0xD3); // Set display offset
	ssd1306_command(0x00); // No offset
	ssd1306_command(SSD1306_MEMORY_MODE); // Memory addressing mode
	ssd1306_command(0x00); // Horizontal addressing mode
	ssd1306_command(SSD1306_DISPLAY_RAM); // Output follows RAM content
	ssd1306_command(SSD1306_DISPLAY_ON); // Display on
}
//------------------------------------------------------------------------------
void ssd1306_command(uint8_t command) 
{
	digitalWrite(CS1, LOW);		// CS1 = 0; 

	digitalWrite(DC, LOW); 		// DC = 0; // Command mode
	spi_write(command);
	
	digitalWrite(CS1, HIGH);	// CS1 = 1;
}
//------------------------------------------------------------------------------
void ssd1306_data(uint8_t data) 
{
	digitalWrite(CS1, LOW);		// CS1 = 0; 
	
	digitalWrite(DC, HIGH); 	// DC = 1; // Data mode
	spi_write(data);
	
	digitalWrite(CS1, HIGH);	// CS1 = 1;
}
//------------------------------------------------------------------------------
void ssd1306_setColumn(uint8_t start, uint8_t end) 
{
	ssd1306_command(0x21); 	// Set Column Address command
	ssd1306_command(start); // Start column
	ssd1306_command(end);   // End column
}
//------------------------------------------------------------------------------
void ssd1306_print(uint8_t row, uint8_t col, char text[]) 
{
	ssd1306_command(SSD1306_SET_PAGE_ADDR | row); // Set page address 
	ssd1306_setColumn(col, 127);									// Set column address
	
	while(*text)
	{
		writeChar(*text++);
	}
}
//------------------------------------------------------------------------------
//										//Currently not working
void ssd1306_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap) 
{
	uint8_t page, col;
	uint16_t index = 0;

	for(page = 0; page < (height / 8); page++) 
	{
		ssd1306_command(0xB0 + page); // Set page address
		ssd1306_command(0x00);       	// Set lower column address
		ssd1306_command(0x10);       	// Set higher column address
		
		for(col = 0; col < width; col++) 
		{
			ssd1306_data(bitmap[index++]);
		}
	}
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{
	uint8_t col, chunk;
	
	for(col = 0; col < 5; col++)
	{
		chunk = (isPrint(chr)) ? chars[chr - ' '][col] : customChars[0][col];
		
		ssd1306_data(chunk);
	}
		
	ssd1306_data(0x00);														//Space 
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;  // valid range for printable ascii chars
}
//------------------------------------------------------------------------------
void ssd1306_reset(void)
{
	digitalWrite(RST, LOW);		// RST = 0;
	delay_ms(10);
	digitalWrite(RST, HIGH);	// RST = 1;
	delay_ms(10);
}
//------------------------------------------------------------------------------
#endif
