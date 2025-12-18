#ifndef SSD1308_C
#define SSD1308_C
//------------------------------------------------------------------------------
#include "ssd1308_h.h"
//------------------------------------------------------------------------------
void ssd1308_init(void) 
{
	i2c_init(); 
	
	pinMode(RST, OUTPUT, PUSH_PULL);
	
	ssd1308_reset();
	ssd1308_command(SSD1308_DISPLAY_OFF); // Display off
	ssd1308_command(0xD5); // Set display clock divide ratio
	ssd1308_command(0x80); // Suggested ratio
	ssd1308_command(0xA8); // Set multiplex ratio
	ssd1308_command(0x3F); // 1/64 duty
	ssd1308_command(0xD3); // Set display offset
	ssd1308_command(0x00); // No offset
	ssd1308_command(SSD1308_MEMORY_MODE); // Memory addressing mode
	ssd1308_command(0x00); // Horizontal addressing mode
	ssd1308_command(SSD1308_DISPLAY_RAM); // Output follows RAM content
	ssd1308_command(SSD1308_DISPLAY_ON); // Display on
}
//------------------------------------------------------------------------------
void ssd1308_command(uint8_t command) 
{
	i2c_start();
	
	i2c_write(SSD1308_I2C_ADDRESS << 1); // SSD1308 address with write
	i2c_write(0x00); // Command mode
	i2c_write(command);
	
	i2c_stop();
}
//------------------------------------------------------------------------------
void ssd1308_data(uint8_t data) 
{
	i2c_start();
	
	i2c_write(SSD1308_I2C_ADDRESS << 1); // SSD1308 address with write
	i2c_write(0x40); // Data mode
	i2c_write(data);
	
	i2c_stop();
}
//------------------------------------------------------------------------------
void ssd1308_setColumn(uint8_t start, uint8_t end) 
{
	i2c_start();

	i2c_write(SSD1308_I2C_ADDRESS << 1); // SSD1308 I2C address (write)
	i2c_write(0x00); 	// Command mode
	i2c_write(0x21); 	// Set Column Address command
	i2c_write(start); // Start column
	i2c_write(end);   // End column

	i2c_stop();
}
//------------------------------------------------------------------------------
void ssd1308_print(uint8_t row, uint8_t col, char text[]) 
{
	ssd1308_command(SSD1308_SET_PAGE_ADDR | row); // Set page address 
	ssd1308_setColumn(col, 127);									// Set column address
	
	while(*text)
	{
		writeChar(*text++);
	}
}
//------------------------------------------------------------------------------
//										//Currently not working
void ssd1308_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap) 
{
	uint8_t page, col;
	uint16_t index = 0;

	for(page = 0; page < (height / 8); page++) 
	{
		ssd1308_command(0xB0 + page); // Set page address
		ssd1308_command(0x00);       	// Set lower column address
		ssd1308_command(0x10);       	// Set higher column address
		
		for(col = 0; col < width; col++) 
		{
			ssd1308_data(bitmap[index++]);
		}
	}
}
//------------------------------------------------------------------------------
void ssd1308_reset(void)
{
  digitalWrite(RST, LOW);   // RST  = 0;
  delay_ms(5);
  digitalWrite(RST, HIGH);  // RST  = 1;
	delay_ms(1);
}
//------------------------------------------------------------------------------
void writeChar(uint8_t chr)
{
	uint8_t col, chunk;
	
	for(col = 0; col < 5; col++)
	{
		chunk = (isPrint(chr)) ? chars[chr - ' '][col] : customChars[0][col];
		
		ssd1308_data(chunk);
	}
		
	ssd1308_data(0x00);														//Space 
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;  // valid range for printable ascii chars
}
//------------------------------------------------------------------------------
#endif
