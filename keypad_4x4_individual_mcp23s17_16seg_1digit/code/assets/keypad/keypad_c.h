#ifndef KEYPAD_C
#define KEYPAD_C
//------------------------------------------------------------------------------
#include "keypad_h.h"            
//------------------------------------------------------------------------------
void keypad_init(void)
{
	mcp23s17_init(KEYPAD_ADDR, chip1);  // All inputs for chip 2
	
	mcp23s17_write(KEYPAD_ADDR, IODIR_A, 0xFF, chip1);		// PORT_A all inputs
	mcp23s17_write(KEYPAD_ADDR, IODIR_B, 0xFF, chip1);		// PORT_B all inputs
}
//------------------------------------------------------------------------------
inline uint16_t keypad_read(void)
{
	uint16_t data[2] = { 0, 0 };
	
	data[0] = mcp23s17_read(KEYPAD_ADDR, GPIO_A, chip1);
	data[1] = mcp23s17_read(KEYPAD_ADDR, GPIO_B, chip1);
	
	return (data[1] << 8) | data[0];
}
//------------------------------------------------------------------------------
int8_t keypad_scan(void)
{
  int8_t keyIndex = -1;  // invalid array index
	uint16_t keyPins = keypad_read();
	
	for(uint8_t btn = 0; btn < 16; btn++)
	{																
		if(keyPins & (01UL << btn))
		{
			keyIndex = btn;		
			break;
		}
	}
  
	return keyIndex;
}
//------------------------------------------------------------------------------
int32_t keypad_char(char str[], char chr, char backspace, char enter)
{
	int8_t pos;
	int32_t number = 0;
	
	pos = getPosChar(str, ' ');
	
	if(chr != backspace)
	{
		if(pos != -1)
		{
			str[pos] = chr;			// Insert character at position
		}
	}
	else
			if(chr == backspace)
			{				
				if(pos == -1)		// if space not found it means all character positions are filled
				{
					pos = strlen(str);		
				}
				
				if(pos > 0)
				{
					str[pos-1] = ' ';		// Insert space character at position before first space char occurrence
				}
			}
	
	number = atoi(str);
			
	if(chr == enter)
		clearStr(str);
			
	return number;	
}
//------------------------------------------------------------------------------
int8_t getPosChar(char str[], char chr)
{
	int8_t i = 0, pos = -1;
	
	for(i = 0; str[i]; i++)
	{
		if(str[i] == chr)
		{
			pos = i; break;
		}
	}
	
	return pos;
}
//------------------------------------------------------------------------------
void clearStr(char str[])
{
	uint8_t i = 0;
	
	while(str[i])
		str[i++] = ' ';
}
//------------------------------------------------------------------------------
#endif


