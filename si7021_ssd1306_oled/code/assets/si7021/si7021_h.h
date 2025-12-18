#ifndef SI7021_H
#define	SI7021_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define		WRITE_CONFIG_CMD	0xE6
#define		READ_CONFIG_CMD		0xE7
#define		RESET_CMD    			0xFE	// Software reset
#define		SI7021_ADDR     	0x40	// 7-bit I2C sensor address (check your datasheet)
#define 	TEMP_NO_HOLD_CMD	0xF3	// Command to initiate a temperature measurement
#define		HUMD_NO_HOLD_CMD	0xF5	// Command to initiate a humidity measurement
//------------------------------------------------------------------------------
//																	 RH				Temp
#define		RES_0    					0x00	// 12bit		14bit
#define		RES_1    					0x01	//  8bit		12bit
#define		RES_2    					0x80	// 10bit		13bit
#define		RES_3    					0x81	// 11bit		11bit
//------------------------------------------------------------------------------
void			si7021_init(uint8_t res);
uint8_t		si7021_readConfig(void);
void			si7021_writeConfig(uint8_t data);
uint16_t	si7021_readConv(uint8_t command);
void			si7021_command(uint8_t command);
float			si7021_calcTemp(uint16_t rawTemp);
float			si7021_calcHumd(uint16_t rawHumd);
uint8_t		si7021_calcCRC(uint8_t data[], uint8_t size);
uint8_t		si7021_isDataValid(uint8_t data[]);
//------------------------------------------------------------------------------
#endif
