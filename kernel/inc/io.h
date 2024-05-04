#pragma once
#include <stdint.h>

/**
 * Read a byte from a port.
 * @param port The port to read from.
 * @return The byte read.
 */
static inline uint8_t inb(uint16_t port) {
	uint8_t res;
	asm volatile ("inb %1, %0" : "=a" (res) : "dN" (port));
	return res;
}

/**
 * Write a byte to a port.
 * @param port The port to write to.
 * @param data The byte to write.
 */
static inline void outb(uint16_t port, uint8_t data) {
	asm volatile ("outb %0, %1" : : "a" (data), "dN" (port));
}
