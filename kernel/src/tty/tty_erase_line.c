#include <tty.h>

void tty_erase_line() {
	t_workspace *w = tty_current_workspace();
	vga_fill_line(0, w->color, w->cursor_y);
	size_t y = w->cursor_y + 1;
	while (y < TTY_HEIGHT && (vga_getc(0, y) & 0xFF))
		vga_fill_line(0, w->color, y++);
	while (w->cursor_y > 0 && (vga_getc(TTY_WIDTH - 1, w->cursor_y - 1) & 0xFF))
		vga_fill_line(0, w->color, --w->cursor_y);
	tty_set_cursor_pos(0, w->cursor_y);
}
