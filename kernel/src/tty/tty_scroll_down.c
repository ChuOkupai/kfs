#include <string.h>
#include <tty.h>

void tty_scroll_down(size_t lines) {
	t_workspace *w = tty_current_workspace();
	if (lines > w->cursor_y)
		lines = w->cursor_y;
	if (!lines)
		return;
	memmove(VGA_MEMORY, VGA_MEMORY + lines * TTY_WIDTH,
		(TTY_BUFSIZE - TTY_WIDTH * lines) * sizeof(t_vga_entry));
	for (size_t y = TTY_HEIGHT - lines; y < TTY_HEIGHT; ++y)
		vga_fill_line(0, w->color, y);
	w->cursor_y -= lines;
}
