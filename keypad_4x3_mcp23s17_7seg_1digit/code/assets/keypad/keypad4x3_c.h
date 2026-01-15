#ifndef KEYPAD4x3_C
#define KEYPAD4x3_C
//------------------------------------------------------------------------------
#include "keypad4x3_h.h"            
//------------------------------------------------------------------------------
void keypad_init(void)
{
	mcp23s17_init();	
	
	mcp23s17_write(KEYPAD_ADDR, IODIR_B, 0xF0);		// 4 inputs (cols), 4 outputs (rows)
}
//------------------------------------------------------------------------------
inline void keypad_rowSelect(uint8_t data)
{ 
	mcp23s17_write(KEYPAD_ADDR, OLAT_B, data);
}
//------------------------------------------------------------------------------
inline uint8_t keypad_readInputs(void)
{
	uint8_t data = 0;
	
	data = mcp23s17_read(KEYPAD_ADDR, GPIO_B);
	
	return data;
}
//------------------------------------------------------------------------------
int8_t keypad_scan(void)
{
  int8_t keyIndex = -1;  // invalid array index
	uint8_t keyPins = 0;
	
	for(uint8_t row = 0; row < 4; row++)
	{
		keypad_rowSelect(0x01 << row);			// row3 = 0x08, row2 = 0x04, row1 = 0x02, row0 = 0x01
		keyPins = keypad_readInputs();
																
		if(keyPins & COL0)
		{
			keyIndex = indices[row][0];				// ROWn, COL0
			break;
		}			
		else
		if(keyPins & COL1) 
		{
			keyIndex = indices[row][1];				// ROWn, COL1
			break;
		}
		else
		if(keyPins & COL2)
		{
			keyIndex = indices[row][2];   		// ROWn, COL2
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


