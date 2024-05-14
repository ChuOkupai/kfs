#include <tty.h>

void tty_erase_line() {
	t_workspace *w = tty_current_workspace();
	tty_move_end_of_line();
	vga_fill(0, TTY_DEFAULT_COLOR, w->rl_start, TTY_BUFSIZE - w->rl_start);
	w->rl_cursor = w->rl_start;
}
