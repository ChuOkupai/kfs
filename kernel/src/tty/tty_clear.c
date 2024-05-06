#include <tty.h>

void tty_clear() {
	t_workspace *w = tty_current_workspace();
	vga_fill(0, w->color);
	w->cursor_index = 0;
}
