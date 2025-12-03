#ifndef SED1565_C
#define	SED1565_C
//------------------------------------------------------------------------------
#include "sed1565_h.h"
//-----------------------Follow Datasheet instructions--------------------------
void sed1565_init(void)
{
  pinMode(RS, OUTPUT, PUSH_PULL);
  pinMode(EN, OUTPUT, PUSH_PULL);

  for(uint8_t i = 0; i < 8; i++)
  {
     pinMode(data_pins[i], OUTPUT, PUSH_PULL); // Set all data pins to LOW initially
  }

	sed1565_startLine(0);
	sed1565_command(bg_white);			// background: white
	sed1565_command(adc_normal);		// address counter: normal
	sed1565_command(display_on);
}
//------------------------------------------------------------------------------
void sed1565_data(uint8_t data)
{
  digitalWrite(RS, HIGH);       // RS = 1;  Data register  ( Strings and characters ).
  
  sed1565_sendBits(data); 
}
//------------------------------------------------------------------------------
void sed1565_command(uint8_t command)
{
  digitalWrite(RS, LOW);        // RS = 0;  Instruction register ( commands ).
  
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
  for(uint8_t i = 0; i < 8; i++)
	{
		uint8_t state = getBit(i, data, MSBFIRST);
    
		digitalWrite(data_pins[i], state);
	}
  
  latch();
}
//------------------------------------------------------------------------------
void sed1565_getBits(uint8_t pinBit[], uint8_t data)
{ 
	uint8_t i;
  
	for(i = 0; i < 8; i++)
  {
    pinBit[i] = ((data >> i) & 0x01) ? 1 : 0;
  }
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
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir)
{ 
  uint8_t pbit = LOW;
  
  switch(dir)
  {
    case(LSBFIRST): pbit = (data & (0x01 << pos)) ? HIGH : LOW; break;      // LSB first
    case(MSBFIRST): pbit = (data & (0x80 >> (7-pos))) ? HIGH : LOW; break;  // MSB first		
  }

  return pbit;
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;
}
//------------------------------------------------------------------------------
void latch()
{
  digitalWrite(EN, HIGH);       // EN  = 1;
  delay_ms(1);
  digitalWrite(EN, LOW);        // EN  = 0;
	delay_ms(1);
}
//------------------------------------------------------------------------------
#endif
