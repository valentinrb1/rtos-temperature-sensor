#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

#include "../FreeRTOS/Source/include/FreeRTOS.h"
#include "../FreeRTOS/Source/include/task.h"
#include "../FreeRTOS/Source/include/queue.h"
#include "../FreeRTOS/Source/include/semphr.h"

#include "../Drivers/LM3S811/DriverLib.h"
#include "../Drivers/LM3S811/hw_memmap.h"
#include "../Drivers/LM3S811/hw_timer.h"
#include "../Drivers/LM3S811/timer.h"

#define FILTER_LENGTH_DEFAULT   10
#define FILTER_TIMEOUT          1000

extern QueueHandle_t xSensorQueue;
extern QueueHandle_t xFilterQueue;

extern int filterLength;

#endif // __COMMON_H__