#ifndef BARGRAPH_C
#define	BARGRAPH_C
//------------------------------------------------------------------------------
#include "bargraph_h.h" 
//------------------------------------------------------------------------------
void bargraph_init(void)
{
	pcf8575_init(0x00, 0x00);
	pcf8575_write(0xff, 0xff);	// Clear ouputs
}
//------------------------------------------------------------------------------
void bargraph_write(uint32_t rawValue)
{
	uint8_t i = map(rawValue, 3, 400, 0, 16);
	uint8_t upper = ~(levels[i] & 0x00FF);
	uint8_t lower = ~(levels[i] >> 8);
	
	pcf8575_write(upper, lower);

}
//------------------------------------------------------------------------------ 
uint8_t map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//------------------------------------------------------------------------------
#endif
