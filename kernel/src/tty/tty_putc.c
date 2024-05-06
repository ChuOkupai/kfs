#include <string.h>
#include <macros.h>
#include <tty.h>

static void move_buf(t_workspace *w, long delta_dst, long delta_src) {
	size_t i = w->cursor_index;
	size_t size = (TTY_BUFSIZE - i - ABS(delta_dst - delta_src)) * sizeof(t_vga_entry);
	memmove(VGA_MEMORY + i + delta_dst, VGA_MEMORY + i + delta_src, size);
}

static void scroll(t_workspace *w) {
	memmove(VGA_MEMORY, VGA_MEMORY + TTY_WIDTH, (TTY_BUFSIZE - TTY_WIDTH) * sizeof(t_vga_entry));
	vga_fill_n(0, w->color, TTY_BUFSIZE - TTY_WIDTH, TTY_WIDTH);
	w->cursor_index -= TTY_WIDTH;
}

void tty_putc(char c) {
	t_workspace *w = tty_current_workspace();
	if (c == '\n') {
		w->cursor_index = TTY_WIDTH * (w->cursor_index / TTY_WIDTH + 1);
		if (w->cursor_index >= TTY_BUFSIZE)
			scroll(w);
	} else if (c == '\b') {
		if (!w->cursor_index || !vga_getc(w->cursor_index - 1))
			return;
		--w->cursor_index;
		move_buf(w, 0, 1);
		vga_putc(0, w->color, TTY_BUFSIZE - 1);
	}
	else {
		if (vga_getc(w->cursor_index)) {
			if (vga_getc(TTY_BUFSIZE - 1))
				tty_scroll_up(1);
			move_buf(w, 1, 0);
		}
		vga_putc(c, w->color, w->cursor_index);
		++w->cursor_index;
		if (w->cursor_index >= TTY_BUFSIZE)
			scroll(w);
	}
}
