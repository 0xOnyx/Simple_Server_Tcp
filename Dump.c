
#include "Dump.h"


void dump(unsigned char *buff, unsigned int lenght)
{
    unsigned char bytes;

    unsigned int i;
    i = 0;

    while(i < lenght)
    {
        bytes = buff[i];
        printf("%02x ", bytes);

        if( (i%16) == 15  ||  i == (lenght-1) )
        {
            unsigned int j;
            j = 0;

            while(j < 15-(i%16))
            {
                printf("   ");
                j++;
            }
            putchar('|');

            j = i-(i%16);

            while(j < i)
            {
                bytes = buff[j];

                if( (bytes > 31) && (bytes < 127) )
                    printf("%c", bytes);
                else
                    putchar('.');

                j++;    
            }


            putchar('\n');
        } 

        i += 1;
    }

}