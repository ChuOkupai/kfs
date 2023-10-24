#include <limits.h>
#include <io.h>
#include <timer.h>

/** On channel 0, Mode 3 with LSB then MSB */
#define PIT_COMMAND 0x36
/** PIT signal frequency in Hz */
#define PIT_SIGNAL_FREQUENCY 1193182
/** PIT timer port address */
#define PIT_PORT_CHANNEL_0 0x40
/** PIT command port address */
#define PIT_PORT_COMMAND 0x43
/** Timer frequency in Hz */
#define TIMER_FREQUENCY 1000
/** PIT frequency in Hz */
#define PIT_MAX_FREQUENCY (PIT_SIGNAL_FREQUENCY / TIMER_FREQUENCY)

static uint16_t pit_read() {
	uint16_t r = inb(PIT_PORT_CHANNEL_0);
	r |= inb(PIT_PORT_CHANNEL_0) << 8;
	return r;
}

static void pit_write(uint16_t v) {
	outb(PIT_PORT_CHANNEL_0, v);
	outb(PIT_PORT_CHANNEL_0, v >> 8);
}

static inline void wait_cycles(uint16_t n) {
	while (pit_read() < 5);
	uint8_t must_dec = 0;
	uint16_t start = pit_read(), prev = start;
	while (n) {
		uint16_t cur = pit_read();
		if (cur < prev) {
			if (cur <= start) {
				if (must_dec)
					--n;
				must_dec = 0;
			}
		} else if (cur - prev > PIT_MAX_FREQUENCY / 2) // reset to max frequency
			must_dec = 1;
		prev = cur;
	}
}

void timer_init() {
	outb(PIT_PORT_COMMAND, PIT_COMMAND);
	pit_write(PIT_MAX_FREQUENCY);
}

void timer_wait(uint16_t ms) {
	wait_cycles(2 * TIMER_FREQUENCY * ms / 1000);
}
