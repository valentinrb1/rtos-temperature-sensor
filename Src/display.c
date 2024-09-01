#include "display.h"

void vDisplayTask(void *pvParameters) {
    (void)pvParameters;

    int filteredValue;

    prvPrintAxis();

    while (1) {
        xQueueReceive(xFilterQueue, &filteredValue, portMAX_DELAY);

        prvPrintData(filteredValue);        
    }
}

static void prvPrintData(int value) {
    prvUpdateNPrint();

    OSRAMImageDraw(decodValue(value), displayIndex, prvGetRowValue(value), 1, 1);

    displayIndex++;

    if (displayIndex > 75)
    {
        prvPrintAxis();
        displayIndex = 13;
    }
}

static void prvPrintAxis() {
    OSRAMClear();

    OSRAMImageDraw(dispFive, 1, 0, 4, 1);
    OSRAMImageDraw(dispZero, 6, 0, 4, 1);
    OSRAMImageDraw(dispZero, 6, 1, 4, 1);

    OSRAMImageDraw(dispLineY, 12, 0, 1, 1);
    OSRAMImageDraw(dispLineY, 12, 1, 1, 1);

    for (uint8_t i = 13; i < 76; i++)
        OSRAMImageDraw(dispLineX, i, 1, 1, 1);
}

static void prvUpdateNPrint() {
    OSRAMImageDraw(dispNLenght, 78, 0, 4, 1);
    OSRAMImageDraw(dispEqual, 83, 0, 2, 1);
    OSRAMImageDraw(decodFilterLenghtNumber(), 86, 0, 9, 1);
}

static const unsigned char* decodFilterLenghtNumber() {
    switch (filterLength)
    {
        case 1:
            return dispOneBis;
            break;
        case 2:
            return dispTwoBis;
            break;
        case 3:
            return dispThreeBis;
            break;
        case 4:
            return dispFourBis;
            break;
        case 5:
            return dispFiveBis;
            break;
        case 6:
            return dispSixBis;
            break;
        case 7:
            return dispSevenBis;
            break;
        case 8:
            return dispEightBis;
            break;
        case 9:
            return dispNineBis;
            break;
        case 10:
            return dispTenBis;
            break;
        case 11:
            return dispElevenBis;
            break;
        case 12:
            return dispTwelveBis;
            break;
        case 13:
            return dispThirteenBis;
            break;
        case 14:
            return dispFourteenBis;
            break;
        case 15:
            return dispFiveteenBis;
            break;
        default:
            break;
    }
}

static const unsigned char* decodValue(uint8_t value) {
    static unsigned char result;

    if (value >= 48)
        result = 0x01;
    else if (value >= 24)
    {
        value -= 24;
        result = 0x80 >> value / 3;
    }
    else
    {
        result  = 0x80 >> value / 3;
        result |= 0x80;
    }
    
    return &result;
}