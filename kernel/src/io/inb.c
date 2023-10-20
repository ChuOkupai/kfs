#include <stdint.h>

uint8_t inb(uint16_t port) {
	uint8_t res;
	asm volatile ("inb %1, %0" : "=a" (res) : "dN" (port));
	return res;
}
