#ifndef DS18B20_C
#define	DS18B20_C
//------------------------------------------------------------------------------
#include "ds18b20_h.h"
//------------------------------------------------------------------------------
/*
void ds18b20_init(int8_t highTemp, int8_t lowTemp, uint8_t res)
{
	pinMode(DQ, OUTPUT, OPEN_DRAIN);
	
	ds18b20_command(WRITE_SCRATCHPAD);
  ds18b20_writeByte(highTemp);	// high temperature threshold for thermostat
  ds18b20_writeByte(lowTemp);		// low temperature threshold for thermostat
  ds18b20_writeByte(res);     	// ADC resolution setting
}
*/
void ds18b20_init(void)
{
	pinMode(DQ, OUTPUT, OPEN_DRAIN);
}
//------------------------------------------------------------------------------
uint8_t ds18b20_reset(void) 
{
	digitalWrite(DQ, LOW);								// DQ = 0; // Pull low
	delay_us(480);
	digitalWrite(DQ, HIGH);		 						// DQ = 1; // Release
	delay_us(70);
	uint8_t presence = !digitalRead(DQ);	// Read presence pulse
	delay_us(410);

	return presence;
}
//------------------------------------------------------------------------------
void ds18b20_writeBit(uint8_t bit) 
{
	digitalWrite(DQ, LOW);					// DQ = 0; // Pull low
	
	if(bit) 
	{
		// write 1
		delay_us(6);
		digitalWrite(DQ, HIGH);				// DQ = 1; // Release
		delay_us(64);
	} 
	else 
			{
				// write 0
				delay_us(60);
				digitalWrite(DQ, HIGH);		// DQ = 1; // Release
				delay_us(10);
			}
}
//------------------------------------------------------------------------------
uint8_t ds18b20_readBit(void) 
{
	uint8_t bit = 0;

	digitalWrite(DQ, LOW);					// DQ = 0; // Pull low
	delay_us(6); 
	digitalWrite(DQ, HIGH);					// DQ = 1; // Release
	delay_us(9);
	bit = digitalRead(DQ);
	delay_us(55);

	return bit;
}
//------------------------------------------------------------------------------
void ds18b20_writeByte(uint8_t byte) 
{
	for(uint8_t i = 0; i < 8; i++) 
	{
		ds18b20_writeBit(byte & 0x01);
		byte >>= 1;
	}
}
//------------------------------------------------------------------------------
uint8_t ds18b20_readByte(void) 
{
	uint8_t byte = 0;

	for(uint8_t i = 0; i < 8; i++) 
	{
		byte >>= 1;
		if(ds18b20_readBit()) 
				byte += 0x80;
	}
	
	return byte;
}
//------------------------------------------------------------------------------
float ds18b20_readTemp(void) 
{
	uint8_t byte[2];
	
	ds18b20_command(CONVERT_TEMP);
	ds18b20_command(READ_SCRATCHPAD);

	byte[0] = ds18b20_readByte();  	// LSB
	byte[1] = ds18b20_readByte();		// MSB
	int16_t rawTemp = (byte[1] << 8) | byte[0];

	return toFloat(rawTemp);
}
//------------------------------------------------------------------------------
uint8_t ds18b20_command(uint8_t data)
{
  if(!ds18b20_reset())
  {
    return 0;             // return 0 if error
  }

  ds18b20_writeByte(SKIP_ROM);   
  ds18b20_writeByte(data);  	

  return 1;
}
//------------------------------------------------------------------------------
uint8_t ds18b20_getSensorData(ds18b20_t *sensor)
{
	uint8_t data[9];
	
  if(!ds18b20_command(CONVERT_TEMP))
  {
    return 0;                      // return 0 if error
  }
  
  while(ds18b20_readByte() == 0);  // wait for conversion complete
  
  if(!ds18b20_command(READ_SCRATCHPAD))
  {
    return 0;
  }
  
  for(uint8_t i = 0; i < 9; i++)
  {
    data[i] = ds18b20_readByte();
  }
	
	ds18b20_setFields(sensor, data);
  
  return 1;                        // OK --> return 1
}
//------------------------------------------------------------------------------
uint8_t ds18b20_calcCRC(uint8_t data[], uint8_t size)
{
  uint8_t i, crc = 0;

  while(size--)
  {
    crc ^= *data++;

    for(i = 0; i < 8; i++) 
    {
      crc = (crc & 0x01) ? (crc >> 1) ^ 0x8C : (crc >> 1);  //0x8C (see datasheet) x^8 + x^4 + x^3 + 1 => 0b 1000 1100
    }
  }
  
  return crc; 
}
//------------------------------------------------------------------------------
uint8_t ds18b20_isDataValid(uint8_t data[], uint8_t size)
{
	uint8_t isValid = 0;
	
	if(ds18b20_calcCRC(data, size) == data[8])	// data[8] == CRC value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
void ds18b20_setFields(ds18b20_t *sensor, uint8_t data[])
{
  if(sensor == NULL || data == NULL) 
  {
    return; // Return if sensor or data pointer is NULL
  }

  sensor->rawTemp = (data[1] << 8) + data[0]; // Combine high and low byte
  sensor->temperature = toFloat(sensor->rawTemp);
  sensor->tempHigh = data[2];                 // High temperature threshold
  sensor->tempLow = data[3];                  // Low temperature threshold);
  sensor->config = data[4];                   // Configuration byte
  sensor->resIndex = (data[4] &  0x60) >> 5; 	// Initialize resolution index
  sensor->crc = data[8];                      // CRC value
}
//------------------------------------------------------------------------------
void ds18b20_convDelay(uint8_t resInd)
{
	switch(resInd) 
	{
		case(0): delay_ms(94);  break;   // 9-bit  res 93.75ms conversion time
		case(1): delay_ms(188); break;   // 10-bit res 187.5ms conversion time
		case(2): delay_ms(375); break;   // 11-bit res 375ms conversion time
		case(3): delay_ms(750); break;   // 12-bit res (Power-up default) 750ms conversion time
	}
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
  float tempr = rawData >> 4;     
  uint16_t count = rawData & FRAC_FLAG;          

  if(count) 
  {
    tempr += (count * 0.0625); // 2^(-4) = 0.0625 (result is in multiples of 0.0625 LSBit for 12-bit res ADC)
  }

  return tempr;
}
//------------------------------------------------------------------------------
#endif
