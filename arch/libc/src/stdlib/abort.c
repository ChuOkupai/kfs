#include "stdlib.h"
#include "stdio.h"

void abort(void)
{
    printf("kernel: panic: abort()\n");
    asm volatile("hlt");
}