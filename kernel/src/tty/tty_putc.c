#include <tty.h>

void tty_putc(char c) {
	t_workspace *w = tty_current_workspace();
	if (c == '\n') {
		w->cursor_x = 0;
		if (++w->cursor_y == VGA_HEIGHT)
			tty_clear();
	} else {
		vga_putc(c, w->color, w->cursor_x, w->cursor_y);
		if (++w->cursor_x == VGA_WIDTH) {
			w->cursor_x = 0;
			if (++w->cursor_y == VGA_HEIGHT)
				tty_clear();
		}
	}
	tty_update_cursor();
}
