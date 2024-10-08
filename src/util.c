#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "util.h"

int run_cmd(char *cmd, ...)
{
    va_list ap;
    char buf[CMDBUFLEN];
    va_start(ap, cmd);
    vsnprintf(buf, CMDBUFLEN, cmd, ap);

    va_end(ap);

    printf("%s\n", buf);

    return system(buf);
}

void hex_dump(char* str, size_t len)
{
    printf("Printing hexdump:\n");
    for (size_t i = 0; i < len; ++i)
    {
        if (i % 8 == 0)
            printf("\n");
        printf("%02x ", (unsigned char)str[i]);
    }
    printf("\n");
}
