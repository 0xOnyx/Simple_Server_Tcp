
#include "Dump.h"


void dump(unsigned char *buff, unsigned int lenght)
{
    unsigned char bytes;

    unsigned int i;
    i = 0;

    while(i < lenght)
    {
        bytes = buff[i];
        printf("%02X ", bytes);
        i += 1;
    }
}