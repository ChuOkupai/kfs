#include <stdlib.h>

void abort(void)
{
    printf("kernel: panic: abort()\n");
    asm volatile("hlt");
}
