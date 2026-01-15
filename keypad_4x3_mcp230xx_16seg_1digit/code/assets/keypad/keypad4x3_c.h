#ifndef KEYPAD4x3_C
#define KEYPAD4x3_C
//------------------------------------------------------------------------------
#include "keypad4x3_h.h"            
//------------------------------------------------------------------------------
void keypad_init(void)
{
	mcp23008_init(KEYPAD_ADDR, 0xF0);  // 4 inputs (cols), 4 outputs (rows)
}
//------------------------------------------------------------------------------
inline void keypad_rowSelect(uint8_t data)
{ 
	mcp23008_write(KEYPAD_ADDR, OLAT, data);
}
//------------------------------------------------------------------------------
inline uint8_t keypad_readInputs(void)
{
	uint8_t keyData = 0;
	
	keyData = mcp23008_read(KEYPAD_ADDR);
	
	return keyData;
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
#endif


