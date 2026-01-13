#ifndef ADS101x_H
#define	ADS101x_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define		REG_CONV								0x00
#define		REG_CONFIG							0x01
#define		REG_LO_THRES						0x02
#define		REG_HI_THRES						0x03	

#define		ADS101x_ADDR_GND  			0x90	// Address Pin tied to ground
#define		ADS101x_ADDR_VDD  			0x92	// Address Pin tied to Vdd
#define		ADS101x_ADDR_SDA  			0x94	// Address Pin tied to SDA
#define		ADS101x_ADDR_SCL  			0x96	// Address Pin tied to SCL
#define		ADS101x_ADDR     				ADS101x_ADDR_GND	// 7-bit I2C sensor address (check datasheet)

#define 	DATA_RATE_8SPS					0x0000	
#define		DATA_RATE_16SPS					0x0020
#define		DATA_RATE_32SPS					0x0040
#define		DATA_RATE_64SPS					0x0060
#define		DATA_RATE_128SPS				0x0080
#define		DATA_RATE_250PS					0x00A0
#define		DATA_RATE_475PS					0x00C0
#define		DATA_RATE_860SPS				0x00E0

#define		MODE_CONT_CONV					0x0000
#define		MODE_SINGLE_SHOT				0x0100

#define		FS_6144mV								0x0000
#define		FS_4096mV								0x0200
#define		FS_2048mV								0x0400
#define		FS_1024mV								0x0600
#define		FS_512mV								0x0800
#define		FS_256mV_0							0x0A00
#define		FS_256mV_1							0x0C00
#define		FS_256mV_2							0x0E00

#define 	AINP_AIN0_AINN_AIN1    	0x0000
#define 	AINP_AIN0_AINN_AIN3    	0x1000
#define 	AINP_AIN1_AINN_AIN3    	0x2000
#define 	AINP_AIN2_AINN_AIN3    	0x3000
#define 	AINP_AIN0_AINN_GND     	0x4000
#define 	AINP_AIN1_AINN_GND     	0x5000
#define 	AINP_AIN2_AINN_GND     	0x6000
#define 	AINP_AIN3_AINN_GND     	0x7000

#define		SINGLE_MODE	        		0x00
#define		DIFFERENTIAL_MODE				0x01

uint16_t sing_channel[] = { 0x4000, 0x5000, 0x6000, 0x7000 };
uint16_t diff_channel[] = { AINP_AIN0_AINN_AIN1, AINP_AIN0_AINN_AIN3, AINP_AIN1_AINN_AIN3, AINP_AIN2_AINN_AIN3 };
//------------------------------------------------------------------------------
void			ads101x_init(void);
uint16_t	ads101x_read(uint8_t reg);
void			ads101x_write(uint8_t reg, uint16_t data);
void 			ads101x_config(uint16_t data);
float			ads101x_getVoltage(uint8_t mode, uint8_t chn);
//------------------------------------------------------------------------------
#endif
