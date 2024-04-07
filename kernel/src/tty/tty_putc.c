#include <string.h>
#include <tty.h>

static void scroll(t_workspace *w) {
	memmove(VGA_MEMORY, VGA_MEMORY + TTY_WIDTH, (TTY_BUFSIZE - TTY_WIDTH) * sizeof(t_vga_entry));
	for (size_t x = 0; x < TTY_WIDTH; ++x)
		vga_putc(' ', w->color, x, TTY_HEIGHT - 1);
	--w->cursor_y;
}

void tty_putc(char c) {
	t_workspace *w = tty_current_workspace();
	if (c == '\n') {
		w->cursor_x = 0;
		if (++w->cursor_y == TTY_HEIGHT)
			scroll(w);
	} else if (c == '\b') {
		if (w->cursor_x > 0)
			--w->cursor_x;
		else if (w->cursor_y > 0) {
			w->cursor_x = TTY_WIDTH - 1;
			--w->cursor_y;
			while (w->cursor_x > 0 && !(vga_getc(w->cursor_x, w->cursor_y) & 0xFF))
				--w->cursor_x;
		}
		vga_putc(0, w->color, w->cursor_x, w->cursor_y);
	}
	else {
		vga_putc(c, w->color, w->cursor_x, w->cursor_y);
		if (++w->cursor_x == TTY_WIDTH) {
			w->cursor_x = 0;
			if (++w->cursor_y == TTY_HEIGHT)
				scroll(w);
		}
	}
	tty_update();
}
