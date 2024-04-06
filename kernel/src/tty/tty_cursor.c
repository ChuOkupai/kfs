#include <io.h>
#include <tty.h>

void tty_set_cursor_pos(uint8_t x, uint8_t y) {
	t_workspace *w = tty_current_workspace();
	w->cursor_x = x;
	w->cursor_y = y;
	tty_update_cursor();
}

void tty_set_cursor_type(t_cursor_type type) {
	const uint8_t cursor_types[] = { 0, 14 };

	g_tty->cursor_type = type;
	outb(0x3D4, 0x0A);
	if (type == CURSOR_TYPE_NONE)
		outb(0x3D5, 0x20);
	else {
		outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_types[type - 1]);
		outb(0x3D4, 0x0B);
		outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
		tty_update_cursor();
	}
}

void tty_update_cursor() {
	if (g_tty->cursor_type != CURSOR_TYPE_NONE) {
		t_workspace *w = tty_current_workspace();
		uint16_t pos = w->cursor_y * VGA_WIDTH + w->cursor_x;
		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t) (pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
	}
}
