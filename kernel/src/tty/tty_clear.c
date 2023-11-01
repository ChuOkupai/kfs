#include <tty.h>

void tty_clear() {
	t_workspace *w = tty_get_current_workspace();
	vga_fill('\0', w->color);
	w->row = 0;
	w->column = 0;
	tty_cursor_update();
}
