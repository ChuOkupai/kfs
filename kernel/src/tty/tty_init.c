#include "tty.h"
#include "vga.h"

static inline void screen_init(t_screen *s) {
	s->row = 0;
	s->column = 0;
	s->color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}

void tty_init(t_tty *t) {
	screen_init(&t->screen);
	tty_clear(t);
}
