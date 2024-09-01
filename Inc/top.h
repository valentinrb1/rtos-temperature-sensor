#ifndef __TOP_H__
#define __TOP_H__

#include <string.h>
#include "common.h"
#include "uartHandler.h"

#define TOP_DELAY ((TickType_t)2000 / portTICK_PERIOD_MS)

void vTopTask(void *pvParameters);

#endif // __TOP_H__