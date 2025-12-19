#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define CLK			PA0 
#define SDOUT		PA1
#define SDIN 		PA2
//------------------------------------------------------------------------------
void spi_init(void)
{
  pinMode(CLK, OUTPUT, PUSH_PULL);
  pinMode(SDOUT, OUTPUT, PUSH_PULL);
  pinMode(SDIN, INPUT, PUSH_PULL);
}
//--------------------------TX: transmit _data-----------------------------------
void spi_write(uint8_t send)
{	
	for(uint8_t tx = 0; tx < 8; tx++)
	{
		digitalWrite(CLK, LOW);        //SCLK = 0;
    digitalWrite(SDOUT, ((send << tx) & 0x80) ? HIGH : LOW);  //MSB first
		digitalWrite(CLK, HIGH);       //SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
uint8_t spi_read(void)
{
  uint8_t data = 0;
  
  for(uint8_t Rx = 0 ; Rx < 8 ; Rx++)
  {
    digitalWrite(CLK, LOW);        //SCLK = 0;
    data += digitalRead(SDIN) << (7-Rx);     //MSB first.
		digitalWrite(CLK, HIGH);       //SCLK = 1;
  }

  return data;
}
//------------------------------------------------------------------------------
#endif
