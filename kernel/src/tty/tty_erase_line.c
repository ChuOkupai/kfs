#include <tty.h>

void tty_erase_line() {
	t_workspace *w = tty_current_workspace();
	size_t start = w->cursor_index - w->cursor_index % TTY_WIDTH;
	vga_fill_n(0, w->color, start, TTY_BUFSIZE - start);
}
