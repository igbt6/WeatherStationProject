/*
 * uart.h
 *
 *  Created on: 10 paü 2014
 *      Author: lukasz
 */

#ifndef UART_H_
#define UART_H_

#include "USART0_DEBUG.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {

	UART0_mod, UART1_mod,

} UART_MODULE;

typedef struct {
  volatile bool uartDataReceivedFlag;
  volatile bool uartDataSentFlag;

} UART_UsrData;

bool uartInit(UART_MODULE uartMod);
bool uartSendData(uint8_t* buf, uint16_t sizeOfBuf);
bool uartReceiveData(uint8_t* buf, uint16_t sizeOfBuf);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* UART_H_ */
