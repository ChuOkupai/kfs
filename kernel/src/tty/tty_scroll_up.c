#include <string.h>
#include <tty.h>

void tty_scroll_up(size_t lines) {
	t_workspace *w = tty_current_workspace();
	if (lines > w->cursor_index / TTY_WIDTH)
		lines = w->cursor_index / TTY_WIDTH;
	if (!lines)
		return;
	memmove(VGA_MEMORY, VGA_MEMORY + lines * TTY_WIDTH,
		(TTY_BUFSIZE - TTY_WIDTH * lines) * sizeof(t_vga_entry));
	vga_fill_n(0, w->color, TTY_BUFSIZE - TTY_WIDTH, TTY_WIDTH * (TTY_HEIGHT - lines));
	w->cursor_index -= lines * TTY_WIDTH;
}
