#ifndef SAA1064_C
#define SAA1064_C
//------------------------------------------------------------------------------
#include "saa1064_h.h"
//------------------------------------------------------------------------------
void saa1064_init(void)
{           	
  i2c_init();     
  
  i2c_start();
	
  i2c_write(SAA1064_ADDRESS);              
	i2c_write(CONTROL_REG); 
	i2c_write(DEVICE_CONFIG); 
	
  i2c_stop();
	
	saa1064_multiData("    ");	// Clear outputs
}
//------------------------------------------------------------------------------
void saa1064_print(const char* format, ...) 
{
	char str[40];
	
	va_list args; // Declare a va_list variable
	va_start(args, format); // Initialize the va_list with the last fixed argument

	// Use vsprintf to print with the provided format and variadic arguments
	vsprintf(str, format, args); 

	va_end(args); // Clean up the va_list
	
	saa1064_multiData(str);
}
//------------------------------------------------------------------------------
void saa1064_multiData(char data[])
{
	i2c_start();    
	
	i2c_write(SAA1064_ADDRESS); 
	i2c_write(DISPLAY_REG);
  saa1064_string(data);			// Display data_ start address. Auto increments on every write.  
	
	i2c_stop();
}
//------------------------------------------------------------------------------
void saa1064_string(char text[])
{
  uint8_t chrPos = 0, i = 0;	
  int8_t  dpPos[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	reverseStr(text);
  setDpPos(dpPos, text);
	
  while(text[i])
  {   
    uint8_t chr = text[i++];  
    
		if(chr != '.' && chr != 194)		// ° is implicitly split into 194 and 176 by the arduino c++ compiler
		{
			writeChar(chr, chrPos, dpPos[chrPos]);
			chrPos++;
		}
  }
}
//------------------------------------------------------------------------------
void writeChar(char chr, uint8_t chrPos, int8_t  dpPos)
{
	uint8_t digit = 0;
	
	digit = getDigit(chrPos, dpPos, chr); // ascii to 7 seg

	i2c_write(digit);
}
//------------------------------------------------------------------------------
uint8_t getDigit(uint8_t charPos, int8_t dpPos, uint8_t chr)
{
	uint8_t digit = 0;
	
	digit = (isDigit(chr)) ? digits[chr - '0'] : getCustomChar(chr);
					
	return (dpPos != -1 && charPos == dpPos) ? digit + DECIMAL_POINT  : digit;
}
//------------------------------------------------------------------------------
void setDpPos(int8_t dpPos[], char chars[])
{
  uint8_t pos = 0; 
	
  for(uint8_t i = 0; chars[i]; i++)
  {
    if(chars[i] == '.')
		{
			dpPos[pos] = pos;
		}
		else
				{
					pos++;
				}
  }
}
//------------------------------------------------------------------------------
uint8_t getCustomChar(char chrAscii)
{
	uint8_t chrCode = 0x00; /* space char by default*/
  
	for(uint8_t i = 0; customChar[0][i]; i++)
	{
		if(toUpper(chrAscii) == customChar[0][i])
		{
			chrCode = customChar[1][i]; break;
		}
	}	
					
	return chrCode;			
}
//------------------------------------------------------------------------------
inline uint8_t isDigit(char chr)
{
	return (chr >= '0' && chr <= '9') ? 1 : 0;
}
//------------------------------------------------------------------------------
inline char toUpper(char chr)
{	
	return (chr >= 'a' && chr <= 'z') ? (chr - 'a' + 'A') : chr;
}
//------------------------------------------------------------------------------
inline char toLower(char chr)
{	
	return (chr >= 'A' && chr <= 'Z') ? (chr - 'a' - 'A') : chr;
}
//------------------------------------------------------------------------------
void reverseStr(char str[]) 
{
  uint8_t i = 0, j = strLen(str) - 1;
	
  while (i < j) 
	{
		char tmp = str[i];
		str[i++] = str[j];
		str[j--] = tmp;
  }
}
//------------------------------------------------------------------------------
uint8_t strLen(char str[])
{
	uint8_t len = 0;
	
	while(*str++)
  {
		len++;
	}
	
	return len;
}
//------------------------------------------------------------------------------
#endif
