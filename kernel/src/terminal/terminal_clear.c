#include "terminal.h"
#include "vga.h"

void terminal_clear(t_terminal *t) {
	vga_fill(' ', t->screen.color);
	t->screen.row = 0;
	t->screen.column = 0;
}
