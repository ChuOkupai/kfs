#include <io.h>
#include <tty.h>

void tty_cursor_set(size_t x, size_t y) {
	if (g_term->cursor_enabled) {
		uint16_t pos = y * VGA_WIDTH + x;
		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t) (pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
	}
}
