#ifndef HC_SR04_H
#define HC_SR04_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
void			hcsr04_tim2_cc1Init(uint8_t trigPin, uint8_t echoPin);
void 			hcsr04_trigger(uint8_t trigPin);
uint32_t	hcsr04_getRisingEdge(void);
uint32_t	hcsr04_getFallingEdge(void);
uint32_t	hcsr04_measureEcho(uint8_t trigPin);
float			hcsr04_getDistance(uint8_t trigPin);
//------------------------------------------------------------------------------
#endif
