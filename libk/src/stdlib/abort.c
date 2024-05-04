#include <stdio.h>

void abort() {
	printf("kernel: panic: abort()\n");
	asm volatile ("hlt");
}
