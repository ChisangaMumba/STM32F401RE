#ifndef BARGRAPH_C
#define	BARGRAPH_C
//------------------------------------------------------------------------------
#include "bargraph_h.h" 
//------------------------------------------------------------------------------
void bargraph_init(void)
{
	shiftReg_init();
}
//------------------------------------------------------------------------------
void bargraph_write(uint32_t rawValue)
{
	uint8_t i = map(rawValue, 3, 400, 0, 16);
	
	shiftReg_digit16(levels[i]);
}
//------------------------------------------------------------------------------ 
uint8_t map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//------------------------------------------------------------------------------
#endif
