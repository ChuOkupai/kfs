#include "private/tty.h"

void tty_setcolor(t_vga_entry_color color) {
	g_term->screen.color = color;
}
