#include <tty.h>

void tty_erase_line() {
	t_workspace *w = tty_current_workspace();
	vga_fill_line(0, w->color, w->cursor_y);
	tty_set_cursor_pos(0, w->cursor_y);
	tty_update();
}
