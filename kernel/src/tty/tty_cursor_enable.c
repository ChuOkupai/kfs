#include <io.h>
#include <tty.h>

void tty_cursor_enable(t_cursor_type type) {
	const uint8_t cursor_types[] = { 0, 14 };
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_types[type]);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
	term_storage()->cursor_enabled = true;
	tty_cursor_update();
}
