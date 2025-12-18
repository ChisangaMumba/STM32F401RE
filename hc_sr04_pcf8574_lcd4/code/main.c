//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/delay/delay_c.h"
#include "./assets/hc_sr04/hc_sr04_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
#define TRIG  PA1		// Trigger can be on any gpio pin 
#define ECHO  PA0		// Channel 1 TIM2 capture compare module pins PA0, PA5, PA15	PA15 is shared with JTAG; PA5 also maps to TIM2_ETR
//------------------------------------------------------------------------------
char str[30];
float distance;
//------------------------------------------------------------------------------
int main(void)
{
	system_config();	// Set Clock to 16Mhz
	lcd_init();
	hcsr04_tim2_cc1Init(TRIG, ECHO);
	
	lcd_string(0,5, "HC-SR04");

	while (1)
	{
		distance = hcsr04_getDistance(TRIG);
		
		sprintf(str, "Dist:%7.2fcm", distance);
		lcd_string(1, 0, str);
		
		delay_ms(60);
	}
}
//------------------------------------------------------------------------------
