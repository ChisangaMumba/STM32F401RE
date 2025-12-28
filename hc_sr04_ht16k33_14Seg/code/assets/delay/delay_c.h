#ifndef DELAY_C
#define DELAY_C
//------------------------------------------------------------------------------
#include <stdint.h>
#include "stm32f4xx.h"
//------------------------------------------------------------------------------
#define SYSCLK_HZ    16000000U
#define CYCLES_PER_US (SYSCLK_HZ/1000000U)
//------------------------------------------------------------------------------
static void delay_init(void)
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // enable trace
	DWT->CYCCNT = 0;                                 // clear cycle counter (Data Watchpoint and Trace - DWT)
	DWT->CTRL   |= DWT_CTRL_CYCCNTENA_Msk;           // enable counter
}
//------------------------------------------------------------------------------
static void delay_us(uint32_t us)
{
	uint32_t start = DWT->CYCCNT;
	uint32_t ticks = us * CYCLES_PER_US;
	while ((DWT->CYCCNT - start) < ticks) { }
}
//------------------------------------------------------------------------------
void delay_ms(uint32_t ms)
{
	while(ms--) 
	{
		delay_us(1000); // Call microsecond delay 1000 times
	}
}
//------------------------------------------------------------------------------
#endif
