#include <string.h>
#include <tty.h>

static void scroll(t_workspace *w) {
	memmove(VGA_MEMORY, VGA_MEMORY + TTY_WIDTH, (TTY_BUFSIZE - TTY_WIDTH) * sizeof(t_vga_entry));
	vga_fill_line(0, w->color, TTY_HEIGHT - 1);
	--w->cursor_y;
}

void tty_putc(char c) {
	t_workspace *w = tty_current_workspace();
	size_t i = w->cursor_y * TTY_WIDTH + w->cursor_x;
	if (c == '\n') {
		w->cursor_x = 0;
		if (++w->cursor_y == TTY_HEIGHT)
			scroll(w);
	} else if (c == '\b') {
		if (!i)
			return;
		if (w->cursor_x > 0)
			--w->cursor_x;
		else if (w->cursor_y > 0 && (vga_getc(TTY_WIDTH - 1, w->cursor_y - 1) & 0xFF)) {
			w->cursor_x = TTY_WIDTH - 1;
			--w->cursor_y;
		}
		i = w->cursor_y * TTY_WIDTH + w->cursor_x;
		memmove(VGA_MEMORY + i, VGA_MEMORY + i + 1, (TTY_BUFSIZE - i - 1) * sizeof(t_vga_entry));
		if (vga_getc(TTY_WIDTH - 1, TTY_HEIGHT - 1) & 0xFF)
			vga_putc(0, w->color, TTY_WIDTH - 1, TTY_HEIGHT - 1);
	}
	else {
		if (vga_getc(w->cursor_x, w->cursor_y) & 0xFF)
			memmove(VGA_MEMORY + i + 1, VGA_MEMORY + i, (TTY_BUFSIZE - i - 1) * sizeof(t_vga_entry));
		vga_putc(c, w->color, w->cursor_x, w->cursor_y);
		if (++w->cursor_x == TTY_WIDTH) {
			w->cursor_x = 0;
			if (++w->cursor_y == TTY_HEIGHT)
				scroll(w);
		}
	}
	tty_update();
}
