#ifndef BMP280_H
#define	BMP280_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define BMP280_I2C_ADDR  0xEE // 0x77 shifted left for write
//------------------------------------------------------------------------------
#define dig_T1_REG       0x88
#define dig_T2_REG       0x8A
#define dig_T3_REG       0x8C
#define dig_P1_REG       0x8E
#define dig_P2_REG       0x90
#define dig_P3_REG       0x92
#define dig_P4_REG       0x94
#define dig_P5_REG       0x96
#define dig_P6_REG       0x98
#define dig_P7_REG       0x9A
#define dig_P8_REG       0x9C
#define dig_P9_REG       0x9E
//------------------------------------------------------------------------------
#define tMSB             0xFA   //temperature MSB register
#define tLSB             0xFB
#define tXLSB            0xFC
#define pMSB             0xF7   //pressure MSB register
#define pLSB             0xF8
#define pXLSB            0xF9
//------------------------------------------------------------------------------
#define CONFIG_REG       0xF5
#define control_reg      0xF4
#define status_reg       0xF3
#define reset_reg        0xE0
#define id_reg           0xD0
#define sleed_mode       0x00
#define forced_mode1     0x01
#define forced_mode2     0x02
#define normal_mode      0x03
//------------------------------------------------------------------------------
#define osrs_t_skip      0x00 // skip temperature measurement
#define osrs_t_x1        0x01 // 1x temperature oversampling
#define osrs_t_x2        0x02 // 2x temperature oversampling
#define osrs_t_x4        0x03 // 4x temperature oversampling
#define osrs_t_x8        0x04 // 8x temperature oversampling
#define osrs_t_x16       0x05 // 16x temperature oversampling
//------------------------------------------------------------------------------
#define osrs_p_skip      0x00 // skip pressure measurement
#define osrs_p_x1        0x01 // 1x pressure oversampling
#define osrs_p_x2        0x02 // 2x pressure oversampling
#define osrs_p_x4        0x03 // 4x pressure oversampling
#define osrs_p_x8        0x04 // 8x pressure oversampling
#define osrs_p_x16       0x05 // 16x pressure oversampling
//------------------------------------------------------------------------------
//  Calibration coefficients
//  See page 23 of BMP280 datasheet (3.11.2 Trimming parameter readout)
//------------------------------------------------------------------------------
typedef struct 
{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
} 
bmp280_calib_coefs;
//------------------------------------------------------------------------------
void     bmp280_init(bmp280_calib_coefs *calib, uint8_t osrs_t, uint8_t osrs_p, uint8_t mode);
void     bmp280_write(uint8_t reg, uint8_t _data);
uint8_t  bmp280_read8(uint8_t regAddr);                 // Reads 8-bit register
uint16_t bmp280_read16(uint8_t regAddr);                // Reads 16-bit register
uint32_t bmp280_readUncomp(uint8_t msb);
float    bmp280_getTemp(bmp280_calib_coefs calib);
float    bmp280_getPres(bmp280_calib_coefs calib);
void     bmp280_getCalib(bmp280_calib_coefs *calib);    // Reads calibration coefficients
//------------------------------------------------------------------------------
int32_t  t_fine;
//------------------------------------------------------------------------------
#endif
