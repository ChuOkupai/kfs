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

/**
 * Wait for a very small amount of time (1 I/O cycle).
 * Uses port 0x80 which is typically used for I/O delay.
 */
static inline void io_wait(void) {
	outb(0x80, 0);
}