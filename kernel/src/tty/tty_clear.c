#include <tty.h>

void tty_clear() {
	t_workspace *w = tty_current_workspace();
	vga_clear(w->color);
	w->rl_cursor = 0;
	w->rl_start = 0;
}
