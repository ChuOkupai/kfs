#include "private/tty.h"

void tty_clear() {
	vga_fill(' ', g_term->screen.color);
	g_term->screen.row = 0;
	g_term->screen.column = 0;
}
