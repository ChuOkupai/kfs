#include <tty.h>

static inline void screen_putc(t_screen *s, char c) {
	if (c == '\n') {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
		return;
	}
	vga_put(c, s->color, s->column, s->row);
	if (++s->column == VGA_WIDTH) {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
	}
}

void tty_putc(char c) {
	screen_putc(&g_term->screen, c);
}
