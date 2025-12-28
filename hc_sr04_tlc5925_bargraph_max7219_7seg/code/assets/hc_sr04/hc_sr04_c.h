#ifndef HC_SR04_C
#define HC_SR04_C
//------------------------------------------------------------------------------
#include "../hc_sr04/hc_sr04_h.h"
//------------------------------------------------------------------------------
#define SYSCLK_HZ    16000000U
//#define CYCLES_PER_US (SYSCLK_HZ/1000000U)
//------------------------------------------------------------------------------
void hcsr04_tim2_cc1Init(uint8_t trigPin, uint8_t echoPin) 
{
	// 1. Enable TIM2 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	__DSB();

	// 2. Timer base: tick = 1 µs
	TIM2->PSC  = SYSCLK_HZ/1000000U - 1;  // prescaler
	TIM2->ARR  = 0xFFFF;                  // maximum auto-reload

	// 3. CC1 channel = input, map to TI1
	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM2->CCMR1 |=  TIM_CCMR1_CC1S_0;     // CC1S = 01

	// 4. Capture on rising edge (default CC1P=0), enable capture
	TIM2->CCER  &= ~TIM_CCER_CC1P;
	TIM2->CCER  |=  TIM_CCER_CC1E;

	// 5. Start timer
	TIM2->CR1   |=  TIM_CR1_CEN;
	
	// 6. Set GPIO TRIGGER and ECHO
	pinMode(trigPin, OUTPUT, PUSH_PULL, NO_PU_PD);
	pinMode(echoPin, ALTFUN, PUSH_PULL, NO_PU_PD);
	
	delay_ms(35);
}
//------------------------------------------------------------------------------
void hcsr04_trigger(uint8_t trig) 
{
	// Send 10 µs TRIG pulse
	digitalWrite(trig, LOW);   				// SCLK = 0
	delay_us(2);
	digitalWrite(trig, HIGH);   			// SCLK = 1
	delay_us(10);
	digitalWrite(trig, LOW);   				// SCLK = 0
}
//------------------------------------------------------------------------------
uint32_t hcsr04_getRisingEdge(void)
{
	uint32_t t_rising;
	
	// Reset and capture rising edge
	TIM2->CNT  = 0;
	TIM2->SR  &= ~TIM_SR_CC1IF;       // clear CC1 flag
	TIM2->CCER &= ~TIM_CCER_CC1P;     // rising
	while(!(TIM2->SR & TIM_SR_CC1IF));
	t_rising = TIM2->CCR1;
	
	return t_rising;
}
//------------------------------------------------------------------------------
uint32_t hcsr04_getFallingEdge(void)
{
	uint32_t t_falling;
	
	// Capture falling edge
	TIM2->SR  &= ~TIM_SR_CC1IF;       // clear CC1 flag
	TIM2->CCER |=  TIM_CCER_CC1P;     // falling
	while(!(TIM2->SR & TIM_SR_CC1IF));
	t_falling = TIM2->CCR1;
	
	return t_falling;
}
//------------------------------------------------------------------------------
uint32_t hcsr04_measureEcho(uint8_t trigPin) 
{
	uint32_t t_rising, t_falling, delta;
	
	hcsr04_trigger(trigPin);
	t_rising = hcsr04_getRisingEdge();
	t_falling = hcsr04_getFallingEdge();

	// Compute elapsed (handle overflow)
	if(t_falling >= t_rising)
		delta = t_falling - t_rising;
	else
		delta = (0xFFFF - t_rising) + t_falling;

	return delta; // Return pulse width in microseconds
}
//------------------------------------------------------------------------------
float hcsr04_getDistance(uint8_t trigPin)
{
	uint32_t echo_time = hcsr04_measureEcho(trigPin);

	// -1.0f indicates timeout or out-of-range
	return (echo_time == 0) ? -1.0f : (echo_time / 58.0f); // Convert µs to cm
}
//------------------------------------------------------------------------------
#endif
