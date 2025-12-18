//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/hc_sr04/hc_sr04_c.h"
#include "./assets/max6954/max6954_c.h"
//------------------------------------------------------------------------------
#define TRIG  PA1		// Trigger can be on any gpio pin 
#define ECHO  PA0		// Channel 1 TIM2 capture compare module pins PA0, PA5, PA15	PA15 is shared with JTAG; PA5 also maps to TIM2_ETR
//------------------------------------------------------------------------------
char str[30];
float distance;
//------------------------------------------------------------------------------
int main(void)
{	  
	system_config();				 // Set Clock to 16Mhz	
	max6954_init();
	hcsr04_tim2_cc1Init(TRIG, ECHO);

	while(1)
	{		 
		distance =  hcsr04_getDistance(TRIG);
		
		sprintf(str, "%6ucm", (int)distance); 
		max6954_displayText(str);
		
		delay_ms(120);
	}
}
//------------------------------------------------------------------------------

