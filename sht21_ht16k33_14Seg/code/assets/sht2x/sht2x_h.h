#ifndef SHT2x_H
#define SHT2x_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define SHT21_I2C_ADDRESS 0x80
#define TEMP_MEASURE      0xF3
#define HUMD_MEASURE      0xF5
//------------------------------------------------------------------------------
void sht2x_init(void);
uint16_t sht2x_read(uint8_t command);
float sht2x_getTemp(void);
float sht2x_getHumd(void); 
//------------------------------------------------------------------------------
#endif
