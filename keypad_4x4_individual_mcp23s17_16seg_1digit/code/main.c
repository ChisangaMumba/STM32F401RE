//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/keypad/keypad_c.h"
#include "./assets/sixteenSeg/sixteenSeg_c.h"
//------------------------------------------------------------------------------
const char charset[] = "123A456B789C*0#D/";
int8_t i = -1;		// invalid array index 
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();	// Set Clock to 16Mhz	
	sixteenSeg_init();
	keypad_init();
	
	while(1)
	{ 
		i = keypad_scan();
		if(i != -1)
		{
			sixteenSeg_char(charset[i]);
		}
	}
}
//------------------------------------------------------------------------------
