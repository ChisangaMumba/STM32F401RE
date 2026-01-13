#ifndef DHT22_H
#define	DHT22_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define DATA_PIN  PA5 
//------------------------------------------------------------------------------
typedef struct 
{
  uint16_t rawTemp;
  float    temperature;
	uint16_t rawHumidity;
	float    humidity;
  uint8_t  checksum;        
} dht22_t;
//------------------------------------------------------------------------------
void 		oneWire_start(void);			
uint8_t oneWire_getResponse(void);			
uint8_t oneWire_read8(void);		
uint8_t dht22_calcChecksum(uint8_t sensorData[]);
uint8_t dht22_isDataValid(uint8_t sensorData[]);
uint8_t dht22_getSensorData(dht22_t *sensor);
void 		dht22_setFields(dht22_t *sensor, uint8_t data[]);
float 	calcTempr(int16_t rawData);
//------------------------------------------------------------------------------
#endif
