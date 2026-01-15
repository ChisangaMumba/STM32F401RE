//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/keypad/keypad4x3_c.h"
#include "./assets/sevenSeg/sevenSeg_c.h"
//------------------------------------------------------------------------------
const char charset[] = "123456789C0E";
int8_t i = -1;		// invalid array index 
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();	// Set Clock to 16Mhz	
	sevenSeg_init();
	keypad_init();
	
	while(1)
	{ 
		i = keypad_scan();
		if(i != -1)
		{
			sevenSeg_char(charset[i]);
		}
	}
}
//------------------------------------------------------------------------------

