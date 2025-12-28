#ifndef KS0108_C
#define	KS0108_C
//------------------------------------------------------------------------------
#include "ks0108_h.h"
//-----------------------Follow Datasheet instructions--------------------------
void ks0108_init(void)
{
  pinMode(RS, OUTPUT, PUSH_PULL);
  pinMode(EN, OUTPUT, PUSH_PULL);
	
	pinMode(CS1, OUTPUT, PUSH_PULL);
  pinMode(CS2, OUTPUT, PUSH_PULL);
	
	// deselect both chips initially
	digitalWrite(CS1, HIGH);
	digitalWrite(CS2, HIGH); 
  
	// or you can use a loop to set all data pins at once:
  for(uint8_t i = 0; i < 8; i++)
  {
    pinMode(data_pins[i], OUTPUT, PUSH_PULL); // Set all data pins to LOW initially
  }
  
  ks0108_command(display_on, 3);  // 3 => write to both halves of the chips   
  ks0108_fill(CLEAR);
}
//------------------------------------------------------------------------------
void ks0108_command(uint8_t command, uint8_t chipNo)
{
	ks0108_chip(chipNo);
	
  digitalWrite(RS, LOW);          // RS = 0;     //  Instruction register ( commands ).
  ks0108_sendBits(command);
}
//------------------------------------------------------------------------------
void ks0108_data(uint8_t data, uint8_t chipNo)
{
	ks0108_chip(chipNo);
	
  digitalWrite(RS, HIGH);         // RS = 1;     //  Data register  ( strings and characters ).
  ks0108_sendBits(data);
}
//------------------------------------------------------------------------------
void ks0108_print(uint8_t row, uint8_t col, uint8_t fontNo, const char* format, ...)
{
	char str[30];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
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
          ks0108_data(bitmap[e], 2);    //Write to Chip 2
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
void ks0108_sendBits(uint8_t data)
{
  for(uint8_t i = 0; i < 8; i++)
	{
		uint8_t state = getBit(i, data, MSBFIRST);
    
		digitalWrite(data_pins[i], state);
	}

  latch();
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
    case(1): digitalWrite(CS2, HIGH); digitalWrite(CS1, LOW); break;  	// Selects Chip 1. NB: Both are Active LOW!
    case(2): digitalWrite(CS2, LOW);  digitalWrite(CS1, HIGH); break;  	// Selects Chip 2
    case(3): digitalWrite(CS2, LOW);  digitalWrite(CS1, LOW); break;  	// Selects Both
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
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir)
{ 
  uint8_t pbit = LOW;
  
  switch(dir)
  {
		case(LSBFIRST): pbit = (0x01 & (data >> pos)) ? HIGH : LOW; break; 		 // LSB first	
    case(MSBFIRST): pbit = (0x80 & (data << pos)) ? HIGH : LOW; break;     // MSB first	
  }

  return pbit;
}
//------------------------------------------------------------------------------
void writeChar(uint8_t fontNo, char chr)
{
	uint8_t row = (isPrint(chr)) ? chr - ' ' : 96;	// 0 - 95: standard ascii. While 96 is the position of the degree symbol in the charset
	const uint8_t fontSz = (fontNo == 0) ? 6 : 8;		// 5 rows + space = 6 for 5 x 7 font 
	const uint8_t *font  = (fontNo == 0) ? &font5x7[row * fontSz] : &font8x8[row * fontSz];
	
	ks0108_bitmap(font, fontSz);
}
//------------------------------------------------------------------------------
void latch(void)
{
  digitalWrite(EN, HIGH);   // EN  = 1;
  delay_us(1);
  digitalWrite(EN, LOW);    // EN = 0;
	delay_us(1);
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; // valid ascii range for printable characters
}
//------------------------------------------------------------------------------
#endif
