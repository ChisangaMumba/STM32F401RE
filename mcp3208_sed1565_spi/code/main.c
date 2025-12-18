//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/mcp320x/mcp320x_c.h"
#include "./assets/sed1565/sed1565_c.h"
//------------------------------------------------------------------------------
char str[40];
float volts[7];
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();			// Set Clock to 16Mhz	
	sed1565_init();
	mcp320x_init();
	
	sed1565_print(0, 27, "(MCP3208 adc)");
	sed1565_print(1, 50, "Lm35");
	
	while(1)
	{ 			
		// LM35 produces voltage equivalent to temperature
		// DIFFERENTIAL_MODE or SINGLE_MODE
		volts[0] = mcp320x_getVoltage(SINGLE_MODE, 0);	
		volts[1] = mcp320x_getVoltage(SINGLE_MODE, 1);
		volts[2] = mcp320x_getVoltage(SINGLE_MODE, 2);
		volts[3] = mcp320x_getVoltage(SINGLE_MODE, 3);
		volts[4] = mcp320x_getVoltage(SINGLE_MODE, 4);
		volts[5] = mcp320x_getVoltage(SINGLE_MODE, 5);
				
		sprintf(str, "Ch0:%6.2f,Ch1:%6.2f", volts[0] * 100, volts[1] * 100);
		sed1565_print(3, 0, str);
		
		sprintf(str, "Ch2:%6.2f,Ch3:%6.2f", volts[2] * 100, volts[3] * 100);
		sed1565_print(5, 0, str);
		
		sprintf(str, "Ch4:%6.2f,Ch5:%6.2f", volts[4] * 100, volts[5] * 100);
		sed1565_print(7, 0, str);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
