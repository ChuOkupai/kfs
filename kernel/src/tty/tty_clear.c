#include "tty.h"
#include "vga.h"

void tty_clear(t_tty *t) {
	vga_fill(' ', t->screen.color);
	t->screen.row = 0;
	t->screen.column = 0;
}
