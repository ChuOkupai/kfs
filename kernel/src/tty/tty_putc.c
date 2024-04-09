#include <string.h>
#include <macros.h>
#include <tty.h>

static void move_buf(t_workspace *w, long delta_dst, long delta_src) {
	size_t i = w->cursor_y * TTY_WIDTH + w->cursor_x;
	size_t size = (TTY_BUFSIZE - i - ABS(delta_dst - delta_src)) * sizeof(t_vga_entry);
	memmove(VGA_MEMORY + i + delta_dst, VGA_MEMORY + i + delta_src, size);
}

static void scroll(t_workspace *w) {
	memmove(VGA_MEMORY, VGA_MEMORY + TTY_WIDTH, (TTY_BUFSIZE - TTY_WIDTH) * sizeof(t_vga_entry));
	vga_fill_line(0, w->color, TTY_HEIGHT - 1);
	--w->cursor_y;
}

void tty_putc(char c) {
	t_workspace *w = tty_current_workspace();
	if (c == '\n') {
		w->cursor_x = 0;
		if (++w->cursor_y == TTY_HEIGHT)
			scroll(w);
	} else if (c == '\b') {
		if (!w->cursor_x && !w->cursor_y)
			return;
		if (w->cursor_x > 0)
			--w->cursor_x;
		else if (w->cursor_y > 0 && (vga_getc(TTY_WIDTH - 1, w->cursor_y - 1) & 0xFF)) {
			w->cursor_x = TTY_WIDTH - 1;
			--w->cursor_y;
		}
		move_buf(w, 0, 1);
		vga_putc(0, w->color, TTY_WIDTH - 1, TTY_HEIGHT - 1);
	}
	else {
		if (vga_getc(w->cursor_x, w->cursor_y) & 0xFF)
			move_buf(w, 1, 0);
		vga_putc(c, w->color, w->cursor_x, w->cursor_y);
		if (++w->cursor_x == TTY_WIDTH) {
			w->cursor_x = 0;
			if (++w->cursor_y == TTY_HEIGHT)
				scroll(w);
		}
	}
}
