#include "syshead.h"
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

void hex_dump(char *str, size_t len)
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

void eprint(char *str, ...)
{
    va_list ap;
    char buf[200];
    va_start(ap, str);
    vsnprintf(buf, 200, str, ap);
    va_end(ap);

    perror(buf);
}