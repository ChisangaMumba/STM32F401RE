#ifndef KS0108_C
#define	KS0108_C
//------------------------------------------------------------------------------
#include "ks0108_h.h"
//------------------------------------------------------------------------------
void ks0108_init(void)
{   
	mcp23s17_init(0x00, 0x00); // Initialize mcp23008 with all pins low (outputs)
  ks0108_command(display_on, 3);  // 3 => write to both halves of the chips   
  ks0108_fill(CLEAR);
}
//------------------------------------------------------------------------------
void ks0108_command(uint8_t command, uint8_t chipNo)
{
	ks0108_chip(chipNo);
	
	uint8_t ctrlCommands = CS | 0;		// RS = 0;	// Instruction register ( commands ).
	
  mcp23s17_write(OLAT_A, ctrlCommands);          
	mcp23s17_write(OLAT_B, command);
	
	ks0108_latch(ctrlCommands);
}
//------------------------------------------------------------------------------
void ks0108_data(uint8_t data, uint8_t chipNo)
{
	ks0108_chip(chipNo);
	
	uint8_t ctrlCommands = CS | 1;		// RS = 1;	// Data register ( strings and characters ).
	
  mcp23s17_write(OLAT_A, ctrlCommands);          
	mcp23s17_write(OLAT_B, data);
	
	ks0108_latch(ctrlCommands);
}
//------------------------------------------------------------------------------
void ks0108_print(uint8_t row, uint8_t col, uint8_t fontNo, const char* format, ...)
{
	char str[30];
	
	va_list args; 		// Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); 		// Clean up the va_list
	
	ks0108_string(row, col, fontNo, str);
}
//------------------------------------------------------------------------------
void ks0108_string(uint8_t row, uint8_t col, uint8_t fontNo, char text[])
{
  ks0108_setAddress(row, col);  // Set coordinates.

  while(*text)		// Loop until null terminator.
  {
		writeChar(fontNo, *text++);
	}
}
//------------------------------------------------------------------------------
void ks0108_bitmap(const uint8_t *bitmap, int elements)
{
  for(int e = 0 ; e < elements ; e++)
  {
    if(column < pgWidth)
    {
      ks0108_data(bitmap[e], 1);       	// Write to Chip 1
    }
    else
        if(column < glcdWidth)
        {
          ks0108_column(column);
          ks0108_data(bitmap[e], 2);    // Write to Chip 2
        }
    column++;
  }
}
//------------------------------------------------------------------------------
void ks0108_image(const uint8_t *image)
{
  for(int pg = 0; pg < pgLen ;pg++)
  {
		ks0108_setAddress(pg, 0);
    ks0108_bitmap(&image[pg*glcdWidth] , glcdWidth);
  }
}
//------------------------------------------------------------------------------
void ks0108_startline(uint8_t line)
{
	ks0108_command(0xC0 | line, 3);		// 0xC0 represents Line 0. Write to Chip 1 and 2
}
//------------------------------------------------------------------------------
void ks0108_setAddress(uint8_t row, uint8_t col)
{
	ks0108_command(rowAddr[row], 3);	// 3 => both chips selected
	ks0108_column(col);
}
//------------------------------------------------------------------------------
void ks0108_column(uint16_t col)
{
  column = col;                     // column is a global variable that keeps track of column infomation
	
  if( col < pgWidth )
  {
    col = 0x40 | col;               // 0x40 represents Column 0
    ks0108_command(col, 1);
  }
  else
      if( col < glcdWidth )
      {
        col = 0x40 | (col - pgWidth);
        ks0108_command(col, 2);
      }
}
//------------------------------------------------------------------------------
void ks0108_chip(uint8_t chip)
{
  switch(chip)
  {
    case(1): CS = 0x04; break;  	// Selects Chip 1. NB: Both are Active LOW!
    case(2): CS = 0x08; break;  	// Selects Chip 2
    case(3): CS = 0x00; break;  	// Selects Both
  }
}
//------------------------------------------------------------------------------
void ks0108_fill(unsigned char fill)
{
  for(int pg = 0; pg < pgLen; pg++)
  {
		ks0108_setAddress(pg, 0);
    
		for(int col = 0; col < glcdWidth; col++)
    {
      ks0108_bitmap(&fill,1);
    }
  } 
}
//------------------------------------------------------------------------------
void ks0108_latch(uint8_t ctrlData) 
{
	mcp23s17_write(OLAT_A, ctrlData | EN_HIGH);
	mcp23s17_write(OLAT_A, ctrlData & EN_LOW);
}
//------------------------------------------------------------------------------
void writeChar(uint8_t fontNo, char chr)
{
	uint8_t row = (isPrint(chr)) ?  chr - ' ' : 96;		// 0 - 95: standard ascii. While 96 is the position of the degree symbol in the charset
	const uint8_t fontSz = (fontNo == 0) ? 6 : 8;			// 5 rows + space = 6 for 5 x 7 font
	const uint8_t *font  = (fontNo == 0) ? &font5x7[row * fontSz] : &font8x8[row * fontSz];
	
	ks0108_bitmap(font, fontSz);
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; // valid ascii range for printable characters
}
//------------------------------------------------------------------------------
#endif
