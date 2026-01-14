#ifndef DHT11_H
#define	DHT11_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define DATA_PIN  PA3 
//------------------------------------------------------------------------------
typedef struct 
{
  int16_t  temperature;
	int16_t  humidity;
  uint8_t  checksum;        
} dht11_t;
//------------------------------------------------------------------------------
void 		oneWire_start(void);			
uint8_t oneWire_getResponse(void);			
uint8_t oneWire_read8(void);		
uint8_t dht11_calcChecksum(uint8_t sensorData[]);
uint8_t dht11_isDataValid(uint8_t sensorData[]);
uint8_t dht11_getSensorData(dht11_t *sensor);
void 		dht11_setFields(dht11_t *sensor, uint8_t data[]);
//------------------------------------------------------------------------------
#endif
