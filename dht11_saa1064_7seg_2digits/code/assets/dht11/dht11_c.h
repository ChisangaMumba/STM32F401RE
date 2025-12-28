#ifndef DHT11_C
#define	DHT11_C
//------------------------------------------------------------------------------
#include "dht11_h.h"
//------------------------------------------------------------------------------
void oneWire_start(void)			
{
	pinMode(DATA_PIN, OUTPUT, PUSH_PULL);

	digitalWrite(DATA_PIN, LOW);					// DQ = 0

	delay_ms(25);	                       	// Hold low for =18 ms
	digitalWrite(DATA_PIN, HIGH);					// DQ = 1
	
	delay_us(30);													// Release and wait 20–40 µs
	pinMode(DATA_PIN, INPUT, PUSH_PULL);	
}
//------------------------------------------------------------------------------
uint8_t oneWire_getResponse(void)			
{
	uint16_t count;
			
	// Wait for DHT to pull line low (~80 µs)
	count = 0;
	while(digitalRead(DATA_PIN) == 1 && count++ < 100) delay_us(1);     // wait for DHT11 low pulse
	if(count >= 100) return 0;
	
	// Wait for DHT to pull line high (~80 µs)
	count = 0;
	while(digitalRead(DATA_PIN) == 0 && count++ < 100) delay_us(1);     // wait for DHT11 high pulse
	if(count >= 100) return 0;
	
	// Wait for DHT to go low again, end of response
	count = 0;
	while(digitalRead(DATA_PIN) == 1 && count++ < 100) delay_us(1);     // wait for DHT11 low pulse
	if(count >= 100) return 0;
	
	return 1;
}
//------------------------------------------------------------------------------
uint8_t oneWire_read8(void)		
{
	uint8_t dataByte = 0;	
	
	for(uint8_t i = 0; i < 8; i++)
	{
		while(digitalRead(DATA_PIN) == 0);   // wait for DHT11 low pulse 
		
		delay_us(30);		
		if(digitalRead(DATA_PIN) == 1)       // If high pulse is greater than 30ms
		{
			dataByte += (0x01 << (7 - i));     // set bit (7 - i)
		}
		
		while(digitalRead(DATA_PIN) == 1);   // wait for DHT11 high pulse
	}
	
	return dataByte;
}
//------------------------------------------------------------------------------
uint8_t dht11_calcChecksum(uint8_t sensorData[])
{
	uint8_t checksum = 0;
	
	for(uint8_t i = 0; i < 4; i++)
	{
		checksum += sensorData[i];
	}
	
	return checksum;
}
//------------------------------------------------------------------------------
uint8_t dht11_isDataValid(uint8_t sensorData[])
{
	uint8_t isValid = 0;
	
	if(dht11_calcChecksum(sensorData) == sensorData[4]) // sensorData[4] == checksum value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
//uint8_t dht11_getSensorData(uint8_t sensorData[])
uint8_t dht11_getSensorData(dht11_t *sensor)
{
	uint8_t sensorData[5];
	
	oneWire_start();
	
	// Start communication with DHT11 sensor
	if(!oneWire_getResponse())
	{
		return 0; // If no response from DHT11, exit the function
	}

	for(uint8_t i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_read8();
	}
	
	if(!dht11_isDataValid(sensorData))
	{
		return 0; // If data is invalid due to checksum error exit the function
	}
	
	dht11_setFields(sensor, sensorData);

	return 1; // Return 1 if data is successfully read
}
//------------------------------------------------------------------------------
void dht11_setFields(dht11_t *sensor, uint8_t data[])
{
	sensor->temperature = (data[3] << 8) + data[2];
	sensor->humidity = (data[1] << 8) + data[0];
	sensor->checksum = data[4];
}
//------------------------------------------------------------------------------
#endif
