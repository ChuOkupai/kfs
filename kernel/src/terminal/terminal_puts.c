#include "terminal.h"
#include "utils.h"

void terminal_puts(t_terminal *term, const char *s) {
	terminal_write(term, s, strlen(s));
}
