
#ifndef __UART_H
#define __UART_H
#include "stm8s.h"
#include "stm8s_uart1.h"
#include "stm8s_uart3.h"

#include <stdio.h>

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
#define RxBufferSize 64

void Uart_Init(void);
void UART1_SendByte(u8 data);
int fputc(int ch, FILE *f);
void UART1_SendString(u8* Data,u16 len);
u8 UART1_ReceiveByte(void);
void USART1_printf( uint8_t *Data,...);
//UART 3
void UART3_SendByte(u8 data);
void UART3_SendString(u8* Data,u16 len);
u8 UART3_ReceiveByte(void);

#endif