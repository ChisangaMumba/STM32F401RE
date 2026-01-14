#ifndef BARGRAPH_C
#define	BARGRAPH_C
//------------------------------------------------------------------------------
#include "bargraph_h.h" 
//------------------------------------------------------------------------------
void bargraph_init(void)
{
	mcp23017_init(0x00,0x00);
}
//------------------------------------------------------------------------------
void bargraph_write(uint32_t rawValue)
{
	uint8_t i = map(rawValue, 0, 100, 0, 16);
	
	mcp23017_write(OLAT_A, levels[i]);
	mcp23017_write(OLAT_B, levels[i] >> 8);
}
//------------------------------------------------------------------------------ 
uint8_t map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//------------------------------------------------------------------------------
#endif
