#ifndef HT16K33_C
#define	HT16K33_C
//------------------------------------------------------------------------------
#include "ht16k33_h.h"
//------------------------------------------------------------------------------
void ht16k33_init(uint8_t brightness)
{     
  i2c_init();           
	
  delay_ms(5);       										// Required after Power On reset to give time to initialize device
 
  ht16k33_on();
  ht16k33_setBrightness(brightness);		// Valid values from 0 - 15
  ht16k33_blink(0);  										// Blink OFF
}
//------------------------------------------------------------------------------
void ht16k33_on(void)
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
void ht16k33_print(const char* format, ...)
{
	char str[40];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
  ht16k33_string(str);
}
//------------------------------------------------------------------------------
void ht16k33_string(char str[])
{
  i2c_start();
	
  i2c_write(HT16K33_ADDRESS);
  i2c_write(DISPLAY_MEMORY);     // Display data start address. Auto increments on every write.
  ht16k33_write(str);
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void ht16k33_write(char str[])
{	
  uint8_t chrPos = 0;
  int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};	
		
  setDpPos(dpPos, str);
	
  while(*str)
  {
		uint8_t chr = *str++;
		
		if(chr != '.' && chr != 194)		//° is implicitly split into 194 and 176 by the arduino c++ compiler
		{
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		}
  }
}
//------------------------------------------------------------------------------
void ht16k33_readButtons(uint8_t btnData[])
{
	i2c_start();
	
  i2c_write(HT16K33_ADDRESS | 0);	// write
  i2c_write(KEY_MEMORY);          
	i2c_restart();
	i2c_write(HT16K33_ADDRESS | 1);	// read
	btnData[0] = i2c_read(ACK);
	btnData[1] = i2c_read(ACK);
	btnData[2] = i2c_read(ACK);
	btnData[3] = i2c_read(ACK);
	btnData[4] = i2c_read(ACK);
	btnData[5] = i2c_read(NACK);
	
  i2c_stop();
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos, int8_t dpPos)
{	
  uint8_t digit = getDigit(chr, chrPos, dpPos); //ascii to 7 seg

  i2c_write(digit);			// Lower byte  (D7 - D0)
  i2c_write(0);					// Higher byte (D15 - D8) Unused in 7 seg display
}
//------------------------------------------------------------------------------
//          									ascii to 7 segment
//------------------------------------------------------------------------------
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos)
{
  uint8_t digit = 0;

  digit = (isPrint(chr)) ? chars[chr - ' '] : custom_chars[0];  // custom char is ° symbol
	
  return (dpPos != -1 && chrPos == dpPos) ? digit + DECIMAL_POINT : digit; 
}
//------------------------------------------------------------------------------
void setDpPos(int8_t dpPos[], char chars[])
{
  uint8_t i, pos = 0; 
	
  for(i = 0; chars[i]; i++)
  {
    if(chars[i] == '.')
	{
		dpPos[pos-1] = pos - 1;
	}
	else
		{
			pos++;
		}
  }
}
//------------------------------------------------------------------------------
inline uint8_t isPrint(char chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;  // valid range for printable ascii chars
}
//------------------------------------------------------------------------------
#endif	/* HT16K33_C */

