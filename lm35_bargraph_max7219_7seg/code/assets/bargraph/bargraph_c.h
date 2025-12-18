#ifndef BARGRAPH_H
#define	BARGRAPH_H
//------------------------------------------------------------------------------
#include "../74hc595/74hc595_c.h"
//------------------------------------------------------------------------------
void		bargraph_init(void);
void		bargraph_write(uint32_t rawValue);
uint8_t map(long x, long in_min, long in_max, long out_min, long out_max); 
//------------------------------------------------------------------------------
void bargraph_init(void)
{
	shiftReg_init();
}
//------------------------------------------------------------------------------
void bargraph_write(uint32_t rawValue)
{
	uint8_t levels[9] = { 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF };
	uint8_t indx = map(rawValue, 0, 150, 0, 8);
	
	shiftReg_write(levels[indx]);
}
//------------------------------------------------------------------------------ 
uint8_t map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//------------------------------------------------------------------------------
#endif
