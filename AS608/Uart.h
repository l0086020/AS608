#ifndef _UART_H_
#define _UART_H_

#include <reg52.h>

void Uart_Init(void);
void Uart_Send_Byte(unsigned char c);
unsigned char Uart_Receive_Byte(void);

#endif