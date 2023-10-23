#include <limits.h>
#include <io.h>
#include <timer.h>

#include <string.h>
#include <tty.h>
#include <ps2.h>

#define BUFFER_SIZE 11

void	pint(uint16_t n)
{
	char		buf[BUFFER_SIZE];
	size_t		i;
	uint16_t	t;

	t = n;
	i = BUFFER_SIZE;
	while (t || i == BUFFER_SIZE)
	{
		buf[--i] = t % 10 + '0';
		t /= 10;
	}
	tty_write(buf + i, BUFFER_SIZE - i);
}

void	pintendl(uint16_t n)
{
	pint(n);
	tty_putc('\n');
}

static void wait_kb_input(int code) {
	while (read_ps2_data() != code);
}

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

void timer_init() {
	outb(PIT_PORT_COMMAND, PIT_COMMAND);
	pit_write(PIT_MAX_FREQUENCY);
}

void wait_cycles(uint16_t n) {
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

void timer_wait(uint16_t ms) {
	tty_puts("max theoric frequency: ");
	pintendl(PIT_MAX_FREQUENCY);
	uint16_t start;
	start = pit_read();
	pintendl(start);
	for (uint16_t i = 0; i < 1000; ++i) {
		wait_cycles(10 * TIMER_FREQUENCY);
		tty_clear();
		pintendl(i);
	}
	wait_kb_input(0x1C);
	for (uint16_t i = 0; i < 1000; ++i) {
		tty_clear();
		while (pit_read() > 20);
		int invalid_flag = 0;
		for (uint16_t j = 0, prev = pit_read(); j < VGA_HEIGHT - 1; ++j) {
			uint16_t cur = pit_read();
			pint(cur);
			if (cur > prev) {
				tty_puts(" !");
				invalid_flag = 1;
			}
			tty_putc('\n');
			prev = cur;
		}
		wait_kb_input(invalid_flag ? 0x39 : 0x1C);
	}
	ms = 0;
}
