#ifndef DS1621_H
#define	DS1621_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//----------------------------DS1621--------------------------------------------
#define CONFIG_REG   0xAC
#define TEMP_REG     0xAA
#define TH_REG    	 0xA1
#define TL_REG    	 0xA2
#define START_CONV   0xEE
#define STOP_CONV    0x22
#define READ_COUNTER 0xA8
#define READ_SLOPE   0xA9
#define CONT_CONV    0x02
#define POL_HIGH     0x02
#define Rd           1
#define Wr           0
#define FRAC_FLAG    0x0080
#define DS1621_ADDR   0x90
//------------------------------------------------------------------------------
void 		ds1621_init(int16_t tempH, int16_t tempL);
void    ds1621_config(uint8_t command);
void    ds1621_convertCmd(uint8_t command);
uint8_t ds1621_read1ByteReg(uint8_t deviceReg);
int16_t ds1621_read2ByteReg(uint8_t deviceReg);
void    ds1621_write2ByteReg(uint8_t deviceReg, uint16_t settings);
float 	ds1621_getTemp(uint8_t regName);
float 	toFloat(int16_t tempr);
//------------------------------------------------------------------------------
#endif
