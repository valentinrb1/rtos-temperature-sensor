#include "main.h"

QueueHandle_t xSensorQueue;
QueueHandle_t xFilterQueue;

unsigned long runtimeCounter = 0;

int main(void)
{
	prvSetupHardware();

    xSensorQueue = xQueueCreate(QUEUE_SIZE, sizeof(int));
    xFilterQueue = xQueueCreate(QUEUE_SIZE, sizeof(int));
	
    xTaskCreate(vSensorTask, "SensTask", configMINIMAL_STACK_SIZE, NULL, SENSOR_TASK_PRIORITY, &xSensorTaskHandle);
    xTaskCreate(vFilterTask, "FiltTask", configMINIMAL_STACK_SIZE, NULL, FILTER_TASK_PRIORITY, &xFilterTaskHandle);
	xTaskCreate(vDisplayTask, "DispTask", configMINIMAL_STACK_SIZE, NULL, DISPLAY_TASK_PRIORITY, &xDisplayTaskHandle);
	xTaskCreate(vTopTask, "TopTask", configMINIMAL_STACK_SIZE, NULL, TOP_TASK_PRIORITY, &xTopTaskHandle);
	xTaskCreate(vUartTask, "UartTask", configMINIMAL_STACK_SIZE, NULL, UART_TASK_PRIORITY, &xUartTaskHandle);

	vTaskStartScheduler();

	OSRAMClear();
	OSRAMStringDraw("SCHEDULER START FAILED", 0, 0);

	return 0;
}

static void prvSetupHardware(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	UARTConfigSet(UART0_BASE, BAUD_RATE, UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE);

	OSRAMInit(false);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    vUartSendStr("", 1);
    vUartSendStr("---------------- Task Error ----------------", 1);
    vUartSendStr("Stack Overflow: ", 0);
    vUartSendStr(pcTaskName, 1);
    vUartSendStr("--------------------------------------------", 1);

    vTaskDelete(xTask);
}

static void vTmr0ISR(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    runtimeCounter++;
}

unsigned long vGetTimeCounter(void)
{
    return runtimeCounter;
}

void vConfigureTimerForRunTimeStats(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    IntMasterEnable();
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_32_BIT_TIMER);
    TimerLoadSet(TIMER0_BASE, TIMER_A, 1500);
    TimerIntRegister(TIMER0_BASE,TIMER_A, vTmr0ISR);
    TimerEnable(TIMER0_BASE,TIMER_A);
}