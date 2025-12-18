#ifndef TH02_H
#define	TH02_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define		STATUS_REG    0x00
#define		CONFIG_REG    0x03
#define		DEV_ID_REG    0x11
#define		FAST_MODE    	0x20
#define		TH02_ADDR     0x40      // 7-bit I2C sensor address (check your datasheet)
#define 	TEMP_CMD 			0x11      // Command to initiate a temperature measurement
#define		HUMD_CMD  		0x01      // Command to initiate a humidity measurement
#define 	TEMP_FAST_CMD 0x31      // Command to initiate a temperature measurement
#define		HUMD_FAST_CMD 0x21      // Command to initiate a humidity measurement
//------------------------------------------------------------------------------
void			th02_init(void);
uint8_t 	th02_readDevice(uint8_t command);
uint16_t	th02_readConv(uint8_t command);
void			th02_command(uint8_t command);
float			th02_getTemp(void);
float			th02_getHumd(void);
//------------------------------------------------------------------------------
#endif
