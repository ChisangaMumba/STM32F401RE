#ifndef USART_H
#define USART_H
//------------------------------------------------------------------------------
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define SYSCLK_HZ    16000000U
//------------------------------------------------------------------------------
enum USARTs { usart1 = 1, usart2, usart3, usart4, usart5, usart6 };
//------------------------------------------------------------------------------
void usart_init(uint8_t usartNum, uint32_t baudrate);
void usart_setClock(uint8_t usartNum);
void usart_setPins(uint8_t usartNum);
USART_TypeDef * usart_number(uint8_t usartNum);
IRQn_Type usart_irq(uint8_t usartNum);
int usart_tx(int chr);
int usart_rx(void);
//------------------------------------------------------------------------------
#endif /* USART_H */
