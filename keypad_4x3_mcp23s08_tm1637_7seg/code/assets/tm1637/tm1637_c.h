#ifndef TM1637_C
#define TM1637_C
//------------------------------------------------------------------------------
#include "tm1637_h.h"
//------------------------------------------------------------------------------
void tm1637_init(uint8_t level)
{
  twoWire_init();    
  tm1637_setBrightness(level); // Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void tm1637_print(const char* format, ...)
{    
	char str[40];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
  tm1637_string(str);
}
//------------------------------------------------------------------------------
void tm1637_string(char text[])
{    	
   tm1637_command(DISPLAY_MODE);    
   tm1637_write(text);
}
//------------------------------------------------------------------------------
inline void tm1637_setBrightness(uint8_t level)
{    
   tm1637_command(DISPLAY_CTRL + level); // Valid brightness values: 0 - 8. 0 = display off.
}
//------------------------------------------------------------------------------
void tm1637_write(char text[])
{
   uint8_t chrPos = 0;
   int8_t dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; // Reset dpPos array

   setDpPos(dpPos, text);

   tm1637_initSend(DISPLAY_REG0);
	
   while(*text)
   {        
			uint8_t chr = *text++;
			
			if(chr != '.' && chr != 194) // ° is implicitly split into 194 and 176 by the arduino c++ compiler 
			{
				writeChar(chr, chrPos, dpPos[chrPos]);
				chrPos++;
			}
   }
	
   twoWire_stop();
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos, int8_t dpPos)
{
	uint8_t digit = getDigit(chr, chrPos, dpPos);
  twoWire_write(digit);
  twoWire_ack();
}
//------------------------------------------------------------------------------
void tm1637_command(uint8_t command)
{
  tm1637_initSend(command);
  twoWire_stop();
}
//------------------------------------------------------------------------------
void tm1637_initSend(uint8_t command)
{
	twoWire_start();
	twoWire_write(command);
	twoWire_ack();
}
//------------------------------------------------------------------------------
uint8_t getDigit(char chr, uint8_t charPos, int8_t dpPos)
{
   uint8_t digit = 0;
	
   digit = (isPrint(chr)) ? chars[chr - ' '] : custom_chars[0]; // Default to first custom character if not printable
					
   return (dpPos != -1 && charPos == dpPos) ? (digit | DECIMAL_POINT)  : digit;
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
inline uint8_t isPrint(uint8_t chr)
{
	return (chr >= 32 && chr <= 127) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif	/* tm1637_H */

