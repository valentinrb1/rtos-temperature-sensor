#ifndef __UART_HANDLER_H__
#define __UART_HANDLER_H__

#include "common.h"
#include "utils.h"

void vUartTask(void* pvParameters);

int vUartGet(char* buffer, int length);
void vUartSendStr(const unsigned char *str, int newLine);
void vUartSendInt(int value, int newLine);

#endif // __UART_HANDLER_H__