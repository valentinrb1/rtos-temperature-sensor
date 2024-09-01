#include "sensor.h"

int filterLength;

void vSensorTask(void *pvParameters) {
    (void)pvParameters;

    TickType_t xLastExecutionTime = xTaskGetTickCount();

    while (true) {
        if(uRandGenerator() % 2 == 0)
            (sensorData + 1) > TEMP_MAX ? sensorData = TEMP_MAX : sensorData++;
        else
            (sensorData - 1) < 1 ? sensorData = 1 : sensorData--;

        xQueueSend(xSensorQueue, &sensorData, portMAX_DELAY);
          
        vTaskDelayUntil(&xLastExecutionTime, SENSOR_DELAY);
    }
}

void vFilterTask(void *pvParameters) {
    (void)pvParameters;

    int filteredValue, tempValue;
    int sum = 0;

    filterLength = 10;

    while (1) {
        xQueueReceive(xSensorQueue, &tempValue, portMAX_DELAY);
        
        sum = sum - (sum / filterLength) + tempValue;

        filteredValue = sum / filterLength;

        xQueueSend(xFilterQueue, &filteredValue, portMAX_DELAY);
    }
}
