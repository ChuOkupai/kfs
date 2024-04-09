#include <tty.h>

void tty_move_end_of_line() {
	t_workspace *w = tty_current_workspace();
	size_t i = w->cursor_y * TTY_WIDTH + w->cursor_x;
	while (i < TTY_BUFSIZE && (VGA_MEMORY[i] & 0xFF))
		++i;
	if (i == TTY_BUFSIZE) {
		i -= TTY_WIDTH;
		tty_scroll_up(1);
	}
	tty_set_cursor_pos_from_index(i);
}

void tty_move_start_of_line() {
	t_workspace *w = tty_current_workspace();
	size_t i = w->cursor_y * TTY_WIDTH + w->cursor_x;
	while (i > 0 && (VGA_MEMORY[i - 1] & 0xFF))
		--i;
	tty_set_cursor_pos_from_index(i);
}
