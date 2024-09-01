#ifndef __MAIN_H__
#define __MAIN_H__

#include "sensor.h"
#include "display.h"
#include "uartHandler.h"
#include "top.h"

#include "../Drivers/LM3S811/DriverLib.h"
#include "../Drivers/LM3S811/hw_memmap.h"
#include "../Drivers/LM3S811/timer.h"
#include "../Drivers/LM3S811/hw_timer.h"

static TaskHandle_t xSensorTaskHandle;
static TaskHandle_t xFilterTaskHandle;
static TaskHandle_t xDisplayTaskHandle;
static TaskHandle_t xTopTaskHandle;
static TaskHandle_t xUartTaskHandle;

extern unsigned long runtimeCounter;

#define BAUD_RATE 19200
#define QUEUE_SIZE 10

#define SENSOR_TASK_PRIORITY (tskIDLE_PRIORITY + 4)
#define FILTER_TASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define DISPLAY_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define UART_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define TOP_TASK_PRIORITY (tskIDLE_PRIORITY)

static void prvSetupHardware(void);

static void vTmr0ISR(void);
unsigned long vGetTimeCounter(void);
void vConfigureTimerForRunTimeStats(void);

#endif // __MAIN_H__