//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/keypad/keypad_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
const char charset[] = "123456789*0#";
char str[] = "        ";	// 8 characters wide
int32_t num = 0;
int8_t i = -1;						// invalid array index 
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();						// Set Clock to 16Mhz	
	ht16k33_init(15);   		// Initialize HT16K33 with brightness level 15 
	keypad_init();

	while(1)
	{
		i = keypad_scan();
		
		if(i != -1)
		{
			num = keypad_char(str, charset[i], '*', '#');  // * is the backspace character, # is the Enter char
			//ht16k33_string(str);
			ht16k33_print("%8i", (charset[i] != '#') ? num : 0);
			delay_ms(500); // prevents multiple activations from contact bouncing
		}
		
		delay_ms(10);
	}
}
//------------------------------------------------------------------------------
