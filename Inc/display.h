#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "common.h"
#include "displayCodes.h"

static uint8_t displayIndex = 13;

void vDisplayTask(void *pvParameters);

static void prvPrintAxis();
static void prvPrintData(int value);
static void prvUpdateNPrint();
static const unsigned char* decodValue(uint8_t value);
static const unsigned char* decodFilterLenghtNumber();

#endif // __DISPLAY_H__