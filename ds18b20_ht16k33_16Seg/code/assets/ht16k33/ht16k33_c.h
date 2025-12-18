#ifndef HT16K33_C
#define	HT16K33_C
//------------------------------------------------------------------------------
#include "ht16k33_h.h"
//------------------------------------------------------------------------------
void ht16k33_init(uint8_t brightness)
{     
  i2c_init();           
	
  delay_ms(5);       // Required after Power On reset to give time to initialize device
 
  ht16k33_on();
  ht16k33_setBrightness(brightness);   // Valid values from 0 - 15
  ht16k33_blink(0);  // Blink OFF
}
//------------------------------------------------------------------------------
void ht16k33_on()
{
  i2c_start();
	
  i2c_write(HT16K33_ADDRESS);
  i2c_write(OSCILLATOR_ON);          
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_setBrightness(uint8_t num)
{   
  uint8_t level = ( num <= 15 ) ? num : 1;
	
  i2c_start();
 
  i2c_write(HT16K33_ADDRESS);
  i2c_write(DIGITAL_DIM | level);  // Dimming command. valid values are 0 - 15
 
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_blink(uint8_t data)
{
  i2c_start();
	
  i2c_write(HT16K33_ADDRESS);
  i2c_write(DISPLAY_SETUP | (data << 1));  // Blinking / blanking command
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_displayNum(long number)
{
  char strNum[15];
  sprintf(strNum, "%8li", number);
	
  ht16k33_displayText(strNum);
}
//------------------------------------------------------------------------------
void ht16k33_displayText(char text[])
{
  i2c_start();
	
  i2c_write(HT16K33_ADDRESS);
  i2c_write(DISPLAY_MEMORY);     // Display data start address. Auto increments on every write.
  ht16k33_write(text);
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_write(char text[])
{	
  while(*text)
  {
		writeChar(*text++);
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr)
{	
  uint16_t digit = getDigit(chr);	//ascii to 16 seg

  i2c_write(digit);								// Lower byte  (D7 - D0)
  i2c_write(digit >> 8);					// Higher byte (D15 - D8) 
}
//------------------------------------------------------------------------------
//          									ascii to 16 segment
//------------------------------------------------------------------------------
uint16_t getDigit(char chr)
{
  uint16_t digit = 0;

  digit = (isPrint(chr)) ? chars[chr - ' '] : custom_chars[0];  // custom char is ° symbol
	
  return  digit; 
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;  // valid range for printable ascii chars
}
//------------------------------------------------------------------------------
#endif	/* HT16K33_C */

