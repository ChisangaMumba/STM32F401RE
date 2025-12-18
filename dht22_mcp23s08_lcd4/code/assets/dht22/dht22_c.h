#ifndef DHT22_C
#define	DHT22_C
//------------------------------------------------------------------------------
#include "dht22_h.h"
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
	while(digitalRead(DATA_PIN) == 1 && count++ < 100) delay_us(1);     // wait for DHT low pulse
	if(count >= 100) return 0;
	
	// Wait for DHT to pull line high (~80 µs)
	count = 0;
	while(digitalRead(DATA_PIN) == 0 && count++ < 100) delay_us(1);     // wait for DHT high pulse
	if(count >= 100) return 0;
	
	// Wait for DHT to go low again, end of response
	count = 0;
	while(digitalRead(DATA_PIN) == 1 && count++ < 100) delay_us(1);     // wait for DHT low pulse
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
uint8_t dht22_calcChecksum(uint8_t sensorData[])
{
	uint8_t checksum = 0;
	
	for(uint8_t i = 0; i < 4; i++)
	{
		checksum += sensorData[i];
	}
	
	return checksum;
}
//------------------------------------------------------------------------------
uint8_t dht22_isDataValid(uint8_t sensorData[])
{
	uint8_t isValid = 0;
	
	if(dht22_calcChecksum(sensorData) == sensorData[4]) // sensorData[4] == checksum value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
uint8_t dht22_getSensorData(dht22_t *sensor)
{
	uint8_t sensorData[5];
	
	oneWire_start();
	
	// Start communication with DHT11 sensor
	if(!oneWire_getResponse())
	{
		return 0; // If no response from DHT22, exit the function
	}

	for(uint8_t i = 0; i < 5; i++)
	{
		sensorData[i] = oneWire_read8();
	}

	if(!dht22_isDataValid(sensorData))
	{
		return 0; // If data is invalid due to checksum error exit the function
	}
	
	dht22_setFields(sensor, sensorData);
	
	return 1; // Return 1 if data is successfully read
}
//------------------------------------------------------------------------------
void dht22_setFields(dht22_t *sensor, uint8_t data[])
{
	sensor->rawTemp = (data[2] << 8) + data[3];
	sensor->temperature = calcTempr(sensor->rawTemp);
	sensor->rawHumidity = (data[0] << 8) + data[1];
	sensor->humidity = sensor->rawHumidity / 10.0f; // Convert to float
	sensor->checksum = data[4];
}
//------------------------------------------------------------------------------
float calcTempr(int16_t rawData)
{
	float tempr = rawData;  
   	
	if(rawData & 0x8000) //if 16th bit is a 1, num is negative (sign magnitude signed number)
	{
	  tempr = -1 * (rawData & 0x7fff);
	}

	return tempr/10.0f;
}
//------------------------------------------------------------------------------
#endif
