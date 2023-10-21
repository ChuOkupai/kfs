#include <tty.h>

t_tty g_term_storage;
t_tty *g_term = &g_term_storage;

static inline void screen_init(t_screen *s) {
	s->row = 0;
	s->column = 0;
	s->color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void tty_init() {
	screen_init(&g_term->screen);
	tty_clear();
}
