#include <string.h>
#include <macros.h>
#include <tty.h>

static void move_buf(size_t i, long delta_dst, long delta_src) {
	size_t size = (TTY_BUFSIZE - i - ABS(delta_dst - delta_src)) * sizeof(t_vga_entry);
	memmove(VGA_MEMORY + i + delta_dst, VGA_MEMORY + i + delta_src, size);
}

static void handle_insert(t_workspace *w, char c) {
	if (w->rl_start && vga_getc(TTY_BUFSIZE - 2))
		return;
	if (c == '\n') {
		if (w->rl_start && w->rl_start >= TTY_BUFSIZE - TTY_WIDTH)
			return;
		w->rl_cursor += TTY_WIDTH - (w->rl_cursor % TTY_WIDTH);
	} else {
		move_buf(w->rl_cursor, 1, 0);
		vga_putc(c, w->color, w->rl_cursor);
		++w->rl_cursor;
	}
	if (w->rl_cursor >= TTY_BUFSIZE)
		tty_scroll_up();
}

static void handle_remove(t_workspace *w, char c) {
	if (c == '\b') {
		if (w->rl_cursor == w->rl_start || !vga_getc(w->rl_cursor - 1))
			return;
		--w->rl_cursor;
	}
	move_buf(w->rl_cursor, 0, 1);
	vga_putc(0, w->color, TTY_BUFSIZE - 1);
}

void tty_putc(char c) {
	t_workspace *w = tty_current_workspace();
	c == '\b' || c == 0x7F ? handle_remove(w, c) : handle_insert(w, c);
}
