#include "uartHandler.h"

void vUartTask(void* pvParameters) {
    (void)pvParameters;

    char buffer[32];
    int result;
    TickType_t xLastExecutionTime = xTaskGetTickCount();

    while (1) {
        result = vUartGet(buffer, 32);

        if (result == -1)
            vUartSendStr("\nCommand too long\n", 0);
        else if (result == 1) {
            int newFilterLength = vStrToInt(buffer);
            
            if (newFilterLength > 0 && newFilterLength < 16)
            {
                filterLength = newFilterLength;
                vUartSendStr("\nFilter length set in: ", 0);
                vUartSendInt(filterLength, 1);
            }
            else
            {
                vUartSendStr("\nInvalid filter length. Please, set a value between 1 and 15\n", 0);
                vUartSendStr("\nFilter length set at default: ", 0);
                vUartSendInt(filterLength, 1);
            }
        }

        vTaskDelayUntil(&xLastExecutionTime, ((TickType_t)100 / portTICK_PERIOD_MS));
    }
}

int vUartGet(char* buffer, int length) {
    int i = 0;

    while (i <= length && UARTCharsAvail(UART0_BASE))
        buffer[i++] = UARTCharGet(UART0_BASE);

    buffer[i] = '\0';

    return i > 0 ? (i > length ? -1 : 1) : 0;
}

void vUartSendStr(const unsigned char *str, int newLine)
{
    while (*str != '\0') 
    {
        UARTCharPut(UART0_BASE, *str);
        str++;
    }

    UARTCharPut(UART0_BASE, '\0');

    if (newLine)
        UARTCharPut(UART0_BASE, '\n');
}

void vUartSendInt(int value, int newLine)
{
    char str[32];

    vIntToStr(value, str);

    vUartSendStr(str, newLine);
}
