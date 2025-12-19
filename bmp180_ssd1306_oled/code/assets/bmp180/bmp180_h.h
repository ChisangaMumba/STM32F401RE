#ifndef BMP180_H
#define	BMP180_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define AC1_reg         0xAA
#define AC2_reg         0xAC
#define AC3_reg         0xAE
#define AC4_reg         0xB0
#define AC5_reg         0xB2
#define AC6_reg         0xB4
#define B1_reg          0xB6
#define B2_reg          0xB8
#define MB_reg          0xBA
#define MC_reg          0xBC
#define MD_reg          0xBE
//------------------------------------------------------------------------------
#define CONFIG_REG      0x01
#define READ            0x9A     
#define WRITE           0x9B     
#define STANDBY_MODE	  0x80
#define NORMAL_MODE	    0x00
//------------------------------------------------------------------------------
#define MSB             0xF6
#define LSB             0xF7
#define XLSB            0xF8
#define OSS_0           0x00   // ultra low power mode
#define OSS_1           0x01   // standard mode
#define OSS_2           0x02   // high resolution mode
#define OSS_3           0x03   // ultra high resolution mode  
//------------------------------------------------------------------------------
#define control_reg     0xF4
#define id_reg          0xD0
#define soft_reset_reg  0xE0
#define temp_conv_cmd   0x2E
// Define the bmp180 I2C address
#define BMP180_I2C_ADDR 0xEE // 0x77 shifted left for write                                                              0x03
//------------------------------------------------------------------------------
void     bmp180_init(void);
void     bmp180_write(uint8_t reg, uint8_t _data);
uint8_t  bmp180_read8(uint8_t regAddr);             
uint16_t bmp180_read16(uint8_t regAddr);
uint16_t bmp180_readUncompTemp(void);
float    bmp180_getTemp(void);
uint32_t bmp180_readUncompPress(uint8_t oss);
float    bmp180_getPress(uint8_t oss); // default value for oversampling setting
//------------------------------------------------------------------------------
#endif

