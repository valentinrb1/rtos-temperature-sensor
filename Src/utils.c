#include "../Inc/utils.h"

int prvGetRowValue(uint8_t value)  {
    return value >= 24 ? 0 : 1;
}

int uRandGenerator() {
    g_seed = g_seed * 1103515245 + 12345 ;

    return (int) (g_seed/131072) % 65536 ;
}

int vStrToInt(const char *str) 
{
    int value = 0;

    while (*str >= '0' && *str <= '9') 
    {
        value = value * 10 + (*str - '0');
        ++str;
    }

    if (str != NULL && *str == '\0')
        return value;
    else
        return -1;
}

void vIntToStr(int num, char* str) 
{
    int i = 0;

    if (num == 0)
        str[i++] = '0';
    else
    {
        while (num) 
        {
            str[i++] = num % 10 + '0';
            num = num / 10;
        }
    }

    str[i] = '\0';

    vReverseStr(str, i);
}

static void vReverseStr(char* str, int length) 
{
    int start = 0;
    int end = length - 1;

    while (start < end) 
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
