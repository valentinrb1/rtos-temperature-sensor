#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "common.h"
#include "utils.h"

#define TEMP_MAX                50

#define SENSOR_DELAY	        ((TickType_t)100 / portTICK_PERIOD_MS)
#define NUMBER_OF_VALUES        15

static int sensorData = 20;

void vSensorTask(void *pvParameters);
void vFilterTask(void *pvParameters);

#endif // __SENSOR_H__