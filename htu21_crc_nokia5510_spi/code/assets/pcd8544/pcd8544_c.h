#ifndef PCD8544_C
#define	PCD8544_C
//------------------------------------------------------------------------------
#include "pcd8544_h.h"
//-----------------------Follow Datasheet instructions--------------------------
void pcd8544_init(void)
{
	spi_init(); 
	
  pinMode(CS1, OUTPUT, PUSH_PULL);
  pinMode(RS,  OUTPUT, PUSH_PULL);
  pinMode(RST, OUTPUT, PUSH_PULL);

	pcd8544_reset();
	pcd8544_command(EXTENDED_COMMANDS);			
	pcd8544_command(CONTRAST);		
	pcd8544_command(TEMP_COEFFIECIENT);
	pcd8544_command(BIAS_MODE);
	pcd8544_command(BASIC_COMMANDS);
	pcd8544_command(ALL_SEGS_ON);
	pcd8544_fill(FILL);
	pcd8544_fill(CLEAR);
}
//------------------------------------------------------------------------------
void pcd8544_command(uint8_t command)
{
  digitalWrite(RS, LOW);    // RS = 0;  Instruction register ( commands ).
  
	pcd8544_sendBits(command);
}
//------------------------------------------------------------------------------
void pcd8544_setPosition(uint8_t row, uint8_t col)
{
	pcd8544_command(ROW0 | row);				
	pcd8544_command(COL0 | (col * 6));
}
//------------------------------------------------------------------------------
void pcd8544_print(uint8_t row, uint8_t col, char text[])
{
  pcd8544_setPosition(row, col);  
  
	digitalWrite(RS, HIGH);			// RS = 1;  Data register  ( Strings and characters ).
	
	digitalWrite(CS1, LOW);			// CS1 = 0;
  while(*text)
  {
		uint8_t chr = *text++;
		
		if(chr != 194)    // ° is implicitly split into 194 and 176 by the arduino c++ compiler
    {
			writeChar(chr);
		}
  }
		digitalWrite(CS1, HIGH);	// CS1 = 1;
}
//------------------------------------------------------------------------------
void pcd8544_image(uint8_t *image)
{	
	digitalWrite(RS, HIGH);   // RS = 1;  Data register  ( Strings and characters ).
	
	digitalWrite(CS1, LOW);   // CS1 = 0;
  for(int i = 0; i < 504; i++)
  {
		spi_write(image[i]);
  }
	digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
void pcd8544_fill(uint8_t data)
{	
	digitalWrite(RS, HIGH);   // RS = 1;  Data register  ( Strings and characters ).
	
	digitalWrite(CS1, LOW);   // CS1 = 0;
  for(int i = 0; i < 504; i++)
  {
		spi_write(data);
  }
	digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
void pcd8544_sendBits(uint8_t data)
{
  digitalWrite(CS1, LOW);   // CS1 = 0;
  spi_write(data);
  digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
void pcd8544_reset(void)
{
  digitalWrite(RST, LOW);   // RST  = 0;
  delay_ms(5);
  digitalWrite(RST, HIGH);  // RST  = 1;
	delay_ms(1);
}
//------------------------------------------------------------------------------
void writeChar(char chr)
{
	uint8_t col, chunk;
	
	for(col = 0; col < 5; col++)
	{
		chunk = (isPrint(chr)) ? chars[chr - ' '][col] : customChars[0][col];									
		spi_write(chunk);					
	}
		
	spi_write(0x00);				// Space 
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0; // valid ascii range for printable characters
}
//------------------------------------------------------------------------------
#endif
