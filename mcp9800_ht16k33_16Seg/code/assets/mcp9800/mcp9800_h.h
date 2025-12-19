#ifndef SI7021_H
#define	SI7021_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//----------------------------MCP9800-------------------------------------------
#define  ADDR        0x90    // Device Address
#define  TEMP_REG    0x00
#define  CONFIG_REG  0x01
#define  THYST_REG   0x02
#define  TSET_REG    0x03
#define  RES09_BIT	 0x00		 // 0.5°C (Power-up default)
#define  RES10_BIT	 0x20		 // 0.25°C 
#define  RES11_BIT	 0x40		 // 0.125°C
#define  RES12_BIT	 0x60		 // 0.0625°C
#define  Rd          1
#define  Wr          0
#define  FRAC_FLAG	 0x00F0  // Fractional part of temperature
//------------------------------------------------------------------------------
typedef struct
{
	int8_t	tempHigh;
	int8_t	tempLow;
	uint8_t res;
}mcp9800_config_t;
//------------------------------------------------------------------------------
void     mcp9800_init(int16_t highTemp, int16_t lowTemp, uint8_t res, mcp9800_config_t * configObj);
void     mcp9800_write(uint8_t reg, uint16_t settings);
void     mcp9800_setConfig(uint8_t settings);
void		 mcp9800_setConfigObj(mcp9800_config_t * configObj);
uint8_t  mcp9800_getConfig(void);
int16_t  mcp9800_read(uint8_t reg);
float		 mcp9800_getTemp(void);
void     mcp9800_convDelay(uint8_t resNum);
float    toFloat(int16_t tempr);
//------------------------------------------------------------------------------
#endif
