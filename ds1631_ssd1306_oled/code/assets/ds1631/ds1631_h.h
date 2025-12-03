#ifndef DS1631_H
#define	DS1631_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//----------------------------DS1621--------------------------------------------
#define CONFIG_REG   	0xAC
#define TEMP_REG     	0xAA
#define TH_REG    	 	0xA1
#define TL_REG    	 	0xA2
#define START_CONV   	0x51
#define STOP_CONV    	0x22
#define CONT_CONV    	0x02
#define POL_HIGH     	0x02
#define RES09_BIT    	0x00		 // 0.5000°C  93.75ms conversion time
#define RES10_BIT			0x04		 // 0.2500°C  187.5ms conversion time
#define RES11_BIT			0x08		 // 0.1250°C  375ms conversion time
#define RES12_BIT			0x0C		 // 0.0625°C  (Power-up default) 750ms conversion time
#define Rd           	1
#define Wr           	0
#define FRAC_FLAG    	0x00F0
#define DS1631_ADDR  	0x90
//------------------------------------------------------------------------------
typedef struct
{
	float tempHigh;
	uint8_t tempHFlag;
	float tempLow;
	uint8_t tempLFlag;
	uint8_t resolution;
}ds1631_t;
//------------------------------------------------------------------------------
void 		ds1631_init(int16_t tempH, int16_t tempL, uint8_t resolution, ds1631_t * configObj);
void    ds1631_config(uint8_t command);
void    ds1631_convertCmd(uint8_t command);
uint8_t ds1631_read1ByteReg(uint8_t deviceReg);
int16_t ds1631_read2ByteReg(uint8_t deviceReg);
void    ds1631_write2ByteReg(uint8_t deviceReg, uint16_t settings);
void		ds1631_setConfig(ds1631_t * config);
void 		ds1631_convDelay(uint8_t resNum);
float 	ds1631_getTemp(uint8_t regName);
float 	toFloat(int16_t tempr);
//------------------------------------------------------------------------------
//uint8_t resNum = 0;
//------------------------------------------------------------------------------
#endif
