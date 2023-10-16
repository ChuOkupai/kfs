#include "terminal.h"

void terminal_setcolor(t_terminal *t, uint8_t color) {
	t->screen.color = color;
}
