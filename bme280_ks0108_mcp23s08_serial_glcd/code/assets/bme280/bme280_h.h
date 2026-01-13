#ifndef BME280_H
#define	BME280_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define CS2							 PA4  
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

#define dig_H1_REG       0xA1
#define dig_H2_REG       0xE1  
#define dig_H3_REG       0xE3
#define dig_H4_REG       0xE4
#define dig_H5_REG       0xE5
#define dig_H6_REG       0xE7
//------------------------------------------------------------------------------
#define tMSB             0xFA   // temperature MSB register
#define tLSB             0xFB
#define tXLSB            0xFC
#define hMSB             0xFD   // humidity MSB register
#define hLSB             0xFE 
#define pMSB             0xF7   // pressure MSB register
#define pLSB             0xF8
#define pXLSB            0xF9
//------------------------------------------------------------------------------
#define CONFIG_REG       0xF5
#define control_reg      0xF4
#define status_reg       0xF3
#define ctrl_hum_reg     0xF2
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
#define osrs_h_skip      0x00 // skip humidity measurement
#define osrs_h_x1        0x01 // 1x humidity oversampling
#define osrs_h_x2        0x02 // 2x humidity oversampling
#define osrs_h_x4        0x03 // 4x humidity oversampling
#define osrs_h_x8        0x04 // 8x humidity oversampling
#define osrs_h_x16       0x05 // 16x humidity oversampling
//------------------------------------------------------------------------------
//  Calibration coefficients
//  See page 23 of BMe280 datasheet (3.11.2 Trimming parameter readout)
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
    // Humidity calibration coefficients (if applicable)
    // These are only present in BME280, not in BMP280
    // See page 24 of BME280 datasheet (3.11.3 Humidity trimming parameters)
    // Note: BME280 has humidity sensor, BMP280 does not    
    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t  dig_H6; // Note: dig_H6 is signed, so it is declared as int8_t
    // Note: dig_H4 and dig_H5 are calculated from the raw values read from
} 
bme280_calib_coefs;
//------------------------------------------------------------------------------
void     bme280_init(bme280_calib_coefs *calib, uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t mode);
void     bme280_write(uint8_t reg, uint8_t _data);
uint8_t  bme280_read8(uint8_t regAddr);                 // Reads 8-bit register
uint16_t bme280_read16(uint8_t regAddr);                // Reads 16-bit register
uint32_t bme280_readUncomp(uint8_t msb);
float    bme280_getTemp(bme280_calib_coefs calib);
float    bme280_getPres(bme280_calib_coefs calib);
float    bme280_getHum(bme280_calib_coefs calib);       // Reads humidity (if applicable)
void     bme280_getCalib(bme280_calib_coefs *calib);    // Reads calibration coefficients
//------------------------------------------------------------------------------
int32_t  t_fine;
//------------------------------------------------------------------------------
#endif
