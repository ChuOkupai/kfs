#include <io.h>
#include <pit.h>

#define PIT_CHANNEL_0_DATA_PORT 0x40
#define PIT_COMMAND_PORT 0x43
#define PIT_TICKS_PER_MS 1193

void pit_init(uint32_t frequency) {
	uint32_t divisor = PIT_TICKS_PER_MS * 1000 / frequency;

	// Set the PIT to generate interrupts at the specified frequency
	outb(PIT_COMMAND_PORT, 0x36);
	outb(PIT_CHANNEL_0_DATA_PORT, divisor & 0xFF);
	outb(PIT_CHANNEL_0_DATA_PORT, (divisor >> 8) & 0xFF);
}

void pit_wait(uint32_t milliseconds) {
	uint32_t ticks = milliseconds * PIT_TICKS_PER_MS;

	// Wait for the specified number of PIT ticks
	for (uint32_t i = 0; i < ticks; i++) {
		asm volatile("nop");
	}
}
