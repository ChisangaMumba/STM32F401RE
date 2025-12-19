#ifndef SHT7x_C
#define	SHT7x_C
//------------------------------------------------------------------------------
#include "SHT7x_h.h"
//------------------------------------------------------------------------------
void sht7x_init(void)
{
	pinMode(SHT_CLK, OUTPUT, PUSH_PULL);
}
//------------------------------------------------------------------------------
void SBus_start(void) 
{
	pinMode(SHT_DATA, INPUT, OPEN_DRAIN);		// SHT_DATA = 1
	digitalWrite(SHT_CLK, HIGH);						// SHT_CLK  = 1
	delay_us(5);
	pinMode(SHT_DATA, OUTPUT, OPEN_DRAIN);	// SHT_DATA = 0
	delay_us(5);
	digitalWrite(SHT_CLK, LOW);							// SHT_CLK  = 0
	delay_us(5);
	digitalWrite(SHT_CLK, HIGH);						// SHT_CLK  = 1
	delay_us(5);
	pinMode(SHT_DATA, INPUT, OPEN_DRAIN);		// SHT_DATA = 1
	delay_us(5);
	digitalWrite(SHT_CLK, LOW);							// SHT_CLK  = 0
}
//------------------------------------------------------------------------------
uint8_t SBus_ack(uint8_t ack)
{	
	uint8_t ackState;
	
	// Release DATA to allow sensor to drive an acknowledgment
	pinMode(SHT_DATA, (ack) ? INPUT : OUTPUT, OPEN_DRAIN);	// SHT_DATA = ack;
	digitalWrite(SHT_CLK, HIGH);														// SHT_CLK = 1
	delay_us(3);																						
	digitalWrite(SHT_CLK, LOW);															// SHT_CLK = 0
	pinMode(SHT_DATA, INPUT, OPEN_DRAIN); 									// SHT_DATA = 1
	ackState = digitalRead(SHT_DATA);	// Sensor should pull the line low (0) to acknowledge.

	return (ackState);
}
//------------------------------------------------------------------------------
uint8_t SBus_write(uint8_t data) 
{
	for(uint8_t tx = 0; tx < 8; tx++) 
	{
		pinMode(SHT_DATA, ((data << tx) & 0x80) ? INPUT : OUTPUT, OPEN_DRAIN);  // MSB first
		
		digitalWrite(SHT_CLK, HIGH);			// SHT_CLK = 1
		delay_us(3);
		
		digitalWrite(SHT_CLK, LOW);				// SHT_CLK = 0
		delay_us(3);
	}
	
	return SBus_ack(1);
}
//------------------------------------------------------------------------------
uint8_t SBus_read(uint8_t ack) 
{
	uint8_t rx, data = 0;

	// Release DATA for input
	pinMode(SHT_DATA, INPUT, OPEN_DRAIN);	// SHT_DATA = 1

	for(rx = 0; rx < 8; rx++) 
	{
		digitalWrite(SHT_CLK, HIGH);				// SHT_CLK = 1
		delay_us(3);
		
		data += digitalRead(SHT_DATA) << (7-rx);	// LSB first
		
		digitalWrite(SHT_CLK, LOW);					// SHT_CLK = 0
		delay_us(3);
	}

	SBus_ack(ack);
	
	return data;
}
//------------------------------------------------------------------------------
uint8_t SBus_waitForResult(void) 
{
	uint16_t timeout = 0;
	
	pinMode(SHT_DATA, INPUT, OPEN_DRAIN);		// SHT_DATA = 1 Release DATA (input mode)
	
	while(digitalRead(SHT_DATA)) 
	{
		delay_us(20);
		timeout++;
		if(timeout > TIMEOUT_LIMIT)
			return 0;  // Timeout error
	}
	
	return 1;
}
//------------------------------------------------------------------------------
uint16_t sht7x_read(uint8_t command) 
{
	uint8_t data[2] = { 0, 0 };
	
	SBus_start();
	
	// Send the "Measure Temperature" command (0x03)
	if(!SBus_write(command)) 
	{
		// Here you might flag an error if the sensor does not ACK.
		return 0xFFFF;  // Error value (all bits set)
	}
	
	// Wait for the sensor to complete the measurement
	// Typical conversion time is around 210 ms (check your datasheet)
	if(!SBus_waitForResult()) 
	{
		// Timeout error: sensor did not complete conversion in time.
		return 0xFFFF;
	}
	
	// Read two data bytes: MSB (send ACK) and LSB (send NACK after last byte)
	data[1] = SBus_read(SHT_ACK);		// msb
	data[0] = SBus_read(SHT_NACK);	// lsb

	return (data[1]  << 8) | data[0];
}
//------------------------------------------------------------------------------
// Convert Raw Temperature to Celsius
// According to the SHT1x datasheet, the temperature conversion is given by:
//   Temperature (°C) = -39.6 + 0.01 * raw_value
// (This formula is valid when the sensor is used with a 14-bit resolution.)
//------------------------------------------------------------------------------
float sht7x_getTemp(void) 
{
	uint16_t raw = sht7x_read(TEMP_CMD);
	
	return (-39.6f + 0.01f * (float)raw);
}
//------------------------------------------------------------------------------
// Convert raw humidity reading to percentage.
// The linear approximation (in % RH) might be:
// RH_linear = -2.0468 + 0.0367 * raw + (-1.5955e-6)*raw^2
// and then perform temperature compensation:
// RH_true = (temperature - 25) * (0.01 + 0.00008 * raw) + RH_linear
// Note: Coefficients may vary ° consult the SHT1x datasheet for your sensor.
//------------------------------------------------------------------------------
float sht7x_getHumd(float tempr) 
{
	float rh_linear;
	uint16_t rawHumd = sht7x_read(HUMD_CMD);
	
	rh_linear = -2.0468f + 0.0367f * rawHumd + (-1.5955e-6) * rawHumd * rawHumd;
	
	return (tempr - 25.0f) * (0.01f + 0.00008f * rawHumd) + rh_linear;
}
//------------------------------------------------------------------------------
#endif
