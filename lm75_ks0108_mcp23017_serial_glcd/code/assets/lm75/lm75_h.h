#ifndef LM75_H
#define	LM75_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define  LM75_ADDRESS     0x90     // Address + Read bit
#define  TEMP_REG      		0x00
#define  CONFIG_REG    		0x01
#define  THYST_REG        0x02     
#define  TOS_REG          0x03
#define  FRAC_FLAG        0x00E0   // 0.5 Bit Flag
//------------------------------------------------------------------------------
typedef struct
{
	uint8_t isThermSet;
	float tempHigh;
	float tempLow;
	float temp;
}lm75_t;
//------------------------------------------------------------------------------
void    lm75_init(int16_t tempH, int16_t tempL, lm75_t *sensor);
int16_t lm75_read(uint8_t regAddress);
void    lm75_setConfig(uint8_t _data);
uint8_t lm75_readConfig(void);
void    lm75_write(uint8_t regAddress, int16_t _data);
void		lm75_setSensor(lm75_t *sensor);
float   lm75_getTemp(uint8_t regAddress);
float   toFloat(int16_t tempr);
//------------------------------------------------------------------------------
#endif
