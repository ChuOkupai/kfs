#include "terminal.h"

void terminal_setcolor(t_terminal *t, t_vga_entry_color color) {
	t->screen.color = color;
}
