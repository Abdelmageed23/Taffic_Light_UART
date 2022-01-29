/*
 *
 *
 *
 */

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


uint8_t UART_Init(void);
uint8_t UART_SendByte(uint8_t Data);
uint8_t UART_ReciveByte(uint8_t *Data);
uint8_t UART_SendString(uint8_t *String);
uint8_t UART_ReceiveString(uint8_t *String);
void UART_Flush( void );

void UART_RxCompleteISR(void(*Callback)(void));
void (*UART_RxCompleteCallBack)(void);

void UART_TxCompleteISR(void(*Callback)(void));
void (*UART_TxCompleteCallBack)(void);

#endif
