#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

static int g_seed = 1234;

int prvGetRowValue(uint8_t value);
int uRandGenerator(void);

void vIntToStr(int num, char* str); 
int vStrToInt(const char *str);
static void vReverseStr(char* str, int length);

#endif // __UTILS_H__