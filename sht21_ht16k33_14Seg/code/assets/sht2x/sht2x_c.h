#ifndef SHT2x_C
#define SHT2x_C
//------------------------------------------------------------------------------
#include "sht2x_h.h"
//------------------------------------------------------------------------------
void sht2x_init(void) 
{
    i2c_init();
}
//------------------------------------------------------------------------------
uint16_t sht2x_read(uint8_t regAddress)
{
    uint8_t data[2] = { 0, 0};

    i2c_start();
    
    i2c_write(SHT21_I2C_ADDRESS + 0);
    i2c_write(regAddress);      //measurement command
    i2c_restart();
    i2c_write(SHT21_I2C_ADDRESS + 1) ;
    data[1] = i2c_read(ACK);    // MSB
    data[0] = i2c_read(NACK);   // LSB
    
    i2c_stop();

    return (data[1] << 8) + data[0];
}
//------------------------------------------------------------------------------
float sht2x_getTemp(void)
{
    uint16_t rawTemp = sht2x_read(TEMP_MEASURE);

    return (-46.85 + 175.72/65536 * (float)rawTemp);
}
//------------------------------------------------------------------------------
float sht2x_getHumd(void)
{
    uint16_t rawHumd = sht2x_read(HUMD_MEASURE);

    return (-6.0 + 125.0/65536 * (float)rawHumd);
}
//------------------------------------------------------------------------------
#endif
