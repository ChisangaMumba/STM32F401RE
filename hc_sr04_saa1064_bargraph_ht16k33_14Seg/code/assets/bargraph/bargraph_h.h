#ifndef BARGRAPH_H
#define	BARGRAPH_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include "../saa1064/saa1064_c.h"
//------------------------------------------------------------------------------
void		bargraph_init(void);
void		bargraph_write(uint32_t rawValue);
uint8_t map(long x, long in_min, long in_max, long out_min, long out_max); 
//------------------------------------------------------------------------------
const uint16_t levels[17] = 
{ 
	0x0000, 0x8000, 0xC000, 0xE000, 
	0xF000, 0xF800, 0xFC00, 0xFE00, 
	0xFF00, 0xFF80, 0xFFC0, 0xFFE0,
	0xFFF0, 0xFFF8, 0xFFFC, 0xFFFE,
	0xFFFF,
};
//------------------------------------------------------------------------------
#endif
