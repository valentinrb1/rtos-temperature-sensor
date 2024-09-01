#include "top.h"

static TaskStatus_t *pxTaskStatusArray;

void vTopTask(void *pvParameters) {
    (void)pvParameters;

    TickType_t xLastExecutionTime = xTaskGetTickCount();
    volatile UBaseType_t uxArraySize = uxTaskGetNumberOfTasks();
    pxTaskStatusArray = pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

    while (1) {
        volatile UBaseType_t x;
        unsigned long ulTotalRunTime, ulStatsAsPercentage;

        if (pxTaskStatusArray != NULL)
        {
            uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);

            ulTotalRunTime /= 100UL;

            if (ulTotalRunTime > 0)
            {
                vUartSendStr("\n", 0);
                vUartSendStr("TASK", 0);

                for (int i = 0; i < configMAX_TASK_NAME_LEN - strlen("TASK"); i++)
                    vUartSendStr(" ", 0);

                vUartSendStr("\tTIME\tCPU %\tSTACK MARK\r\n", 0);
                vUartSendStr("-------------------------------------------\r\n", 0);

                for( x = 0; x < uxArraySize; x++ )
                {
                    ulStatsAsPercentage = pxTaskStatusArray[x].ulRunTimeCounter / ulTotalRunTime;

                    vUartSendStr(pxTaskStatusArray[x].pcTaskName, 0);
                    
                    for (int i = 0; i < configMAX_TASK_NAME_LEN - strlen(pxTaskStatusArray[x].pcTaskName); i++)
                        vUartSendStr(" ", 0);
                    
                    vUartSendStr("\t", 0);
                    vUartSendInt(pxTaskStatusArray[x].ulRunTimeCounter, 0);
                    vUartSendStr("\t", 0);
                    
                    if(ulStatsAsPercentage > 0UL)
                        vUartSendInt(ulStatsAsPercentage, 0);
                    else
                        vUartSendInt(0, 0);

                    vUartSendStr("%\t", 0);
                    vUartSendInt(pxTaskStatusArray[x].usStackHighWaterMark, 0);
                    vUartSendStr(" Words\r\n", 0);
                }
            }
        }

        vTaskDelayUntil(&xLastExecutionTime, TOP_DELAY);
    }
}
