#ifndef TC72_H
#define	TC72_H
//------------------------------------------------------------------------------
#include "../spi/Soft_SPI.h"
#include "../delay/delay_c.h"
#define CS2  PA4 
//------------------------------------------------------------------------------
#define CONTROL_REG   0x80
#define START_CONV    0x00
#define LSB_REG       0x01
#define MSB_REG       0x02
#define MANFID_REG    0x03
#define FRAC_FLAG     0x00C0
//------------------------------------------------------------------------------
void    tc72_init(void);
uint8_t tc72_read(uint8_t reg);
float   tc72_getTempr(void);
float   tc72_getTempr2(void);
float   toFloat(int16_t tempr);
//------------------------------------------------------------------------------
#endif
