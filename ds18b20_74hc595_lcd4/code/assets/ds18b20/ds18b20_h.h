#ifndef DS18B20_H
#define	DS18B20_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define DQ		PA5
//------------------------------------------------------------------------------
typedef struct 
{
    uint16_t rawTemp;
    float    temperature;
    int8_t   tempHigh;    // high temperature threshold
    int8_t   tempLow;     // low temperature threshold
    uint8_t  config;
    uint8_t  resIndex;   // resolution index
    uint8_t  crc;        
} ds18b20_t;
//------------------------------------------------------------------------------
#define FRAC_FLAG           0x000F
#define SKIP_ROM            0xCC
#define CONVERT_TEMP    		0x44
#define WRITE_SCRATCHPAD    0x4E
#define READ_POWER_SUPPLY   0xB4
#define RECALL_EEPROM    		0xB8
#define READ_SCRATCHPAD     0xBE
//------------------------------------------------------------------------------
#define RES_09_BIT          0x1F
#define RES_10_BIT          0x3F
#define RES_11_BIT          0x5F
#define RES_12_BIT          0x7F
//------------------------------------------------------------------------------
void 		ds18b20_init(int8_t highTemp, int8_t lowTemp, uint8_t res, ds18b20_t *sensor);
uint8_t ds18b20_reset(void); 
void 		ds18b20_writeBit(uint8_t bit);
uint8_t ds18b20_readBit(void);
void		ds18b20_writeByte(uint8_t byte); 
uint8_t ds18b20_readByte(void) ;
uint8_t ds18b20_command(uint8_t data);
float 	ds18b20_readTemp(void);
uint8_t ds18b20_getSensorData(ds18b20_t *sensor);
uint8_t ds18b20_isDataValid(uint8_t data[], uint8_t size);
uint8_t ds18b20_calcCRC(uint8_t data[], uint8_t size);
void 		ds18b20_setFields(ds18b20_t *sensor, uint8_t data[]);
float 	toFloat(int16_t rawData);
//------------------------------------------------------------------------------
#endif
