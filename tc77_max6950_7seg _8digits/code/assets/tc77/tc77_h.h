#ifndef TC77_H
#define TC77_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
static uint8_t CS1 = PA5;
//------------------------------------------------------------------------------
#define SHUTDOWN     	   	0xFF
#define CONTINUOUS_CONV   0x00
#define FRAC_FLAG         0x0078
//------------------------------------------------------------------------------
void    tc77_init(void);
int16_t tc77_read(void);
float   tc77_getTemp(void);
float   toFloat(int16_t tempr); 
//------------------------------------------------------------------------------
#endif // TC77_H   
