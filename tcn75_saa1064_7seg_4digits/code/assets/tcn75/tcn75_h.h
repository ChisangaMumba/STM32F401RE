#ifndef TCN75_H
#define	TCN75_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
#include "../delay/delay_c.h"
//------------------------------------------------------------------------------
#define  	TCN75_ADDRESS           0x90     // Address + Read bit
#define  	TEMP_REG      					0x00
#define  	CONFIG_REG    					0x01
#define  	THYST_REG            		0x02     
#define  	TOS_REG              		0x03
#define  	FRAC_FLAG            		0x00F0   
//------------------------------------------------------------------------------
#define		RES_09_BIT          		0x00		// 0.5°C
#define		RES_10_BIT          		0x20		// 0.25°C
#define		RES_11_BIT          		0x40		// 0.125°C
#define		RES_12_BIT          		0x60		// 0.0625°C
//------------------------------------------------------------------------------
typedef struct
{
	uint8_t isThermSet;
	uint8_t resol;
	float tempHigh;
	float tempLow;
	float temp;
}tcn75_t;
//------------------------------------------------------------------------------
void    tcn75_init(int16_t tempH, int16_t tempL, uint8_t res, tcn75_t *sensor);
int16_t	tcn75_read(uint8_t regAddress);
void    tcn75_setConfig(uint8_t data);
uint8_t tcn75_readConfig(void);
void    tcn75_set(uint8_t regAddress, int16_t data);
void 		tcn75_setSensor(tcn75_t *sensor);
float   tcn75_getTemp(uint8_t regAddress);
float   toFloat(int16_t tempr);
void 		convDelay(uint8_t resNum);
//------------------------------------------------------------------------------
#endif
