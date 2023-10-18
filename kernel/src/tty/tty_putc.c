#include "tty.h"
#include "vga.h"

static inline void screen_putc(t_screen *s, char c) {
	vga_put(c, s->color, s->column, s->row);
	if (++s->column == VGA_WIDTH) {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
	}
}

void tty_putc(t_tty *t, char c) {
	screen_putc(&t->screen, c);
}