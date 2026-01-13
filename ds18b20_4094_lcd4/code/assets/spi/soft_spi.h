#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define SCLK  PA0 
#define SDOUT PA1
#define SDIN  PA2
//------------------------------------------------------------------------------
void spi_init(void)
{
  pinMode(SCLK, OUTPUT, PUSH_PULL);
  pinMode(SDOUT, OUTPUT, PUSH_PULL);
  pinMode(SDIN, INPUT, PUSH_PULL);
}
//--------------------------TX: transmit _data-----------------------------------
void spi_write(uint8_t send)
{	
	for(uint8_t tx = 0; tx < 8; tx++)
	{
		digitalWrite(SCLK, LOW);        //SCLK = 0;
    digitalWrite(SDOUT, ((send << tx) & 0x80) ? HIGH : LOW);  //MSB first
		digitalWrite(SCLK, HIGH);       //SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
uint8_t spi_read(void)
{
  uint8_t data = 0;
  
  for(uint8_t rx = 0 ; rx < 8 ; rx++)
  {
    digitalWrite(SCLK, LOW);        //SCLK = 0;
    data += digitalRead(SDIN) << (7-rx);     //MSB first.
		digitalWrite(SCLK, HIGH);       //SCLK = 1;
  }

  return data;
}
//------------------------------------------------------------------------------
#endif
