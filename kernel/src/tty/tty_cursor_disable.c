#include <io.h>
#include <tty.h>

void tty_cursor_disable() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
	g_term->cursor_enabled = false;
}
