#include <tty.h>

void tty_erase_line() {
	t_workspace *w = tty_current_workspace();
	size_t start = w->rl_cursor - w->rl_cursor % TTY_WIDTH;
	vga_fill(0, TTY_DEFAULT_COLOR, start, TTY_BUFSIZE - start);
}
