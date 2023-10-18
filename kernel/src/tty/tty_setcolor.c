#include "tty.h"

void tty_setcolor(t_tty *t, t_vga_entry_color color) {
	t->screen.color = color;
}
