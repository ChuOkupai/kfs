#include <keyboard.h>
#include <ps2.h>
#include <tty.h>

void init_keyboard() {
	init_ps2();

	// Enable the keyboard
	write_ps2_command(0xAE);
}

void handle_keyboard_input() {
	static uint8_t caps_lock = 0;

	uint8_t scancode = read_ps2_data();

	if (scancode == 0x2A || scancode == 0x36) {
		// Left or right shift pressed
		tty_puts("Shift pressed\n");
	} else if (scancode == 0xAA || scancode == 0xB6) {
		// Left or right shift released
		tty_puts("Shift released\n");
	} else if (scancode == 0x3A) {
		// Caps lock pressed
		caps_lock = !caps_lock;
		tty_puts("Caps lock pressed, status: ");
		tty_puts(caps_lock ? "on" : "off");
		tty_putc('\n');
	} else if (scancode < 0x80) {
		// Key pressed
		if (scancode == 0x4B) {
			tty_prev_workspace();
			return;
		} else if (scancode == 0x4D) {
			tty_next_workspace();
			return;
		}
		tty_puts("Key pressed: 0x");
		char *b16 = "0123456789ABCDEF";
		tty_putc(b16[scancode >> 4]);
		tty_putc(b16[scancode & 0xF]);
		tty_putc('\n');
	}
}
