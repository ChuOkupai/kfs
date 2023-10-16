#include "terminal.h"

void terminal_write(t_terminal *term, const char *data, size_t size) {
	for (size_t i = 0; i < size; ++i)
		terminal_putc(term, data[i]);
}
