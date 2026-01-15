//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/keypad/keypad4x3_c.h"
#include "./assets/usart/usart_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
const char charset[] = "123456789P0E";
char str[] = "        "; // 8 characters wide
int32_t num = 0;
int8_t i = -1;		// invalid array index  -EHLP 
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();							// Set Clock to 16Mhz	
	max7219_init(1);					// Number of chips connected in parallel
	usart_init(usart2, 9600);	// USARTn, Baudrate = 9600	
	keypad_init();
	printf("Keypad 4 x 3: \r\n");	
	
	while(1)
	{
		i = keypad_scan();
		
		if(i != -1)
		{
			num = keypad_char(str, charset[i], 'P', 'E');  // P is the backspace character, E is the Enter char
			max7219_print("%8i",(charset[i] != 'E') ? num : 0);
			
			if(charset[i] == 'P')
				printf("%c", 0x08);
			else
				printf("%c", charset[i]);
			
			if(charset[i] == 'E')
			{
				printf("\r\nNumber: %i\r\n", num);	
			}
		
			delay_ms(500); // prevents multiple activations from contact bouncing
		}
		
		delay_ms(10);
	}
}
//------------------------------------------------------------------------------

