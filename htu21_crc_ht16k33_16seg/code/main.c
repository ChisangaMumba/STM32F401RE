//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/exti/extInterrupt_c.h"
#include "./assets/bargraph/bargraph_c.h"
#include "./assets/htu21/htu21_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
#define LED PA5
uint8_t isTempMode = 0;
int rawTemp, temp, rawHumd, humd;
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();				// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	htu21_init(RES_3);
	bargraph_init();
	pinMode(LED, OUTPUT, PUSH_PULL, NO_PU_PD);
	extInt_init(PA3, RISING_EDGE);
	
	while(1)
	{ 
		rawHumd = htu21_readConv(HUMD_NO_HOLD_CMD);
		rawTemp = htu21_readConv(TEMP_NO_HOLD_CMD);
		
		// Humidity
		if((isTempMode == 0) && (rawHumd != 0xFFFF))
		{
			humd = (uint16_t) htu21_calcHumd(rawHumd);
			
			ht16k33_print("Humd%3u%c", humd, '%');
			bargraph_write(humd);
		}
		else
				if(rawHumd == 0xFFFF)
					ht16k33_print("Humd Err");
		
		// Temperature
		if((isTempMode == 1) && (rawTemp != 0xFFFF))
		{
			temp = (int) htu21_calcTemp(rawTemp);
			
			ht16k33_print("tmp%3i°C", temp);
			
			bargraph_write((temp >= 0) ? temp : 0);
		}
		else
				if(rawTemp == 0xFFFF)
					ht16k33_print("Temp Err");
		
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------
//						EXTI3_IRQHandler because PA3 was used as exti input 				
//------------------------------------------------------------------------------
void EXTI3_IRQHandler(void)
{
	// External Interrupt (push button)
  if(EXTI->PR & EXTI_PR_PR3)
	{		
		isTempMode = 1 - isTempMode; 		// Toggle state
		digitalWrite(LED, isTempMode);
	}	
	
	EXTI->PR = EXTI_PR_PR3;						// Clear Interrupt flag via assignment 
}
//------------------------------------------------------------------------------
