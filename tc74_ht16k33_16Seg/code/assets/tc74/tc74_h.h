#ifndef TC74_H
#define	TC74_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define  TEMPR_REG     	 0x00
#define  CONFIG_REG      0x01
#define  READ            0x9A     
#define  WRITE           0x9B     
#define  STANDBY_MODE	   0x80
#define  NORMAL_MODE		 0x00
//------------------------------------------------------------------------------
void 		tc74_init(uint8_t data);
void		tc74_config(uint8_t data);
int8_t	tc74_read(uint8_t regAddress);
int8_t	tc74_readTemp(void);
//------------------------------------------------------------------------------
#endif
