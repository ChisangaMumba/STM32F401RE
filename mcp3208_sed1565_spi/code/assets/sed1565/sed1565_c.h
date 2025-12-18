#ifndef SED1565_C
#define	SED1565_C
//------------------------------------------------------------------------------
#include "sed1565_h.h"
//-----------------------Follow Datasheet instructions--------------------------
void sed1565_init(void)
{
	spi_init(); 
	
  pinMode(CS1, OUTPUT, PUSH_PULL);
  pinMode(RS,  OUTPUT, PUSH_PULL);
  pinMode(RST, OUTPUT, PUSH_PULL);

	sed1565_reset();

	sed1565_startLine(0);
	sed1565_command(bg_white);			// background: white
	sed1565_command(adc_normal);		// address counter: normal
	sed1565_command(display_on);
}
//------------------------------------------------------------------------------
void sed1565_data(uint8_t data)
{
  digitalWrite(RS, HIGH);   // RS = 1;  Data register  ( Strings and characters ).
  
	sed1565_sendBits(data);
}
//------------------------------------------------------------------------------
void sed1565_command(uint8_t command)
{
  digitalWrite(RS, LOW);    // RS = 0;  Instruction register ( commands ).
  
	sed1565_sendBits(command);
}
//------------------------------------------------------------------------------
void sed1565_startLine(uint8_t line)
{  
  sed1565_command( 0x40 | line); 
}
//------------------------------------------------------------------------------
void sed1565_setPosition(uint8_t page, uint8_t column)
{
	sed1565_command(0xB0 | (page & 0x0F));
	
	sed1565_command(0x10 | (column >> 4));		// High nibble
	sed1565_command(0x00 | (column & 0x0F));	// Low nibble
}
//------------------------------------------------------------------------------
void sed1565_print(uint8_t row, uint8_t col, char text[])
{
  sed1565_setPosition(row, col);  
  
  while(*text)
  {
		uint8_t chr = *text++;
		
		if(chr != 194)    // ° is implicitly split into 194 and 176 by the arduino c++ compiler
      writeChar(chr);
  }
}
//------------------------------------------------------------------------------
void sed1565_image(uint8_t *image)
{
  uint8_t *img;                     //Stores address of array elements of the image bitmap.
	uint8_t pg, col;
	
  for(pg = 0; pg < pgLen; pg++)
  {
    sed1565_setPosition(pg, 0);      //Pages: 0-7. Set once for each page then self increments in hardware.
		
    img = &image[pg*pgWidth];       //row*pgWidth: Offset value for start address to each "row" in image array. Alleviates need for 2-dimensional array.
    
		for(col = 0; col < pgWidth; col++) //Columns: 0 - 131...since 132 x 64
    {
      sed1565_data( img[col] );     //Dereference the address (via "[]") to get actual value at that postion.
    }
  }
}
//------------------------------------------------------------------------------
void sed1565_sendBits(uint8_t data)
{
  digitalWrite(CS1, LOW);   // CS1 = 0;
  spi_write(data);
  digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
void writeChar(char chr)
{
	uint8_t col, chunk;
	
	for(col = 0; col < 5; col++)
	{
		chunk = (isPrint(chr)) ? chars[chr - ' '][col] : customChars[0][col];									
		sed1565_data(chunk);					
	}
		
	sed1565_data(0x00);						// Space 
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; // valid ascii range for printable characters
}
//------------------------------------------------------------------------------
void sed1565_reset(void)
{
  digitalWrite(RST, LOW);       // RST  = 1;
  delay_ms(5);
  digitalWrite(RST, HIGH);      // RST  = 0;
	delay_ms(1);
}
//------------------------------------------------------------------------------
#endif
