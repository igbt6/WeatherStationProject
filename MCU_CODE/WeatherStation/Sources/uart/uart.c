/*
 * uart.c
 *
 *  Created on: 10 paü 2014
 *      Author: lukasz
 */

#include "uart.h"

typedef struct {
	LDD_TDeviceData* mUart;
	UART_UsrData mUart_UsrData;
} UartHandle;

static UartHandle mUart0Handle;

bool uartInit(UART_MODULE uartMod) {
	if (uartMod == UART0_mod) {
		mUart0Handle.mUart = USART0_DEBUG_Init(&mUart0Handle.mUart_UsrData);
		if (mUart0Handle.mUart == NULL)
			return false;
	} else
		return false; //not supported yet
	return true;
}

bool uartSendData(uint8_t* buf, uint16_t sizeOfBuf) {

	LDD_TError res;
	if (mUart0Handle.mUart != NULL)
		res = USART0_DEBUG_SendBlock(mUart0Handle.mUart, buf, sizeOfBuf);
	if (res != ERR_OK)
		return false;
	while (!mUart0Handle.mUart_UsrData.uartDataSentFlag)
		;
	mUart0Handle.mUart_UsrData.uartDataSentFlag = false;
	return true;

}
bool uartReceiveData(uint8_t* buf, uint16_t sizeOfBuf) {
	LDD_TError res = !ERR_OK;

	if (mUart0Handle.mUart != NULL)
		res = USART0_DEBUG_ReceiveBlock(mUart0Handle.mUart, buf, sizeOfBuf);
	if (res != ERR_OK)
		return false;
	while (!mUart0Handle.mUart_UsrData.uartDataReceivedFlag)
		;
	mUart0Handle.mUart_UsrData.uartDataReceivedFlag = false;
	return true;
}
