//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/keypad/keypad_c.h"
#include "./assets/tm1637/tm1637_c.h"
//------------------------------------------------------------------------------
const char charset[] = "C0=+123-456x789/";
char str[] = "      ";		// 6 characters wide
int32_t num = 0;
int8_t i = -1;						// invalid array index 
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();				// Set Clock to 16Mhz	
	tm1637_init(8);    	// init with brightness value. Valid values: 0 - 8.
	keypad_init();

	while(1)
	{ 
		i = keypad_scan();
		
		if(i != -1)
		{
			num = keypad_char(str, charset[i], 'C', 'E');  // C is the backspace character, E is the Enter char
			tm1637_string(str);
			//tm1637_print("%6i", (charset[i] != 'E') ? num : 0);
			delay_ms(500); // prevents multiple activations from contact bouncing
		}
		
		delay_ms(10);
	}
}
//------------------------------------------------------------------------------
