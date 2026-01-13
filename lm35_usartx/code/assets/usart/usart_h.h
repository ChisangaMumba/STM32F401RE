#ifndef USART_H
#define USART_H
//------------------------------------------------------------------------------
#include <stdbool.h>
#include "../gpio/gpio_c.h"
#define SYSCLK_HZ    16000000U
char is_TReceived = false;
//------------------------------------------------------------------------------
enum USARTs { usart1 = 1, usart2, usart3, usart4, usart5, usart6 };
//------------------------------------------------------------------------------
void usart_init(uint8_t usartNum, uint32_t baudrate);
void usart_setClock(uint8_t usartNum);
void usart_setPins(uint8_t usartNum);
uint8_t usart_writeChar(USART_TypeDef * USARTx, uint8_t ch);
uint8_t usart_readChar(USART_TypeDef * USARTx);
void usart_writeStr(uint8_t usartNum, char str[]) ;
USART_TypeDef * usart_number(uint8_t usartNum);
IRQn_Type usart_irq(uint8_t usartNum);
//------------------------------------------------------------------------------
#endif /* USART_H */
