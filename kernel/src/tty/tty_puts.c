#include "tty.h"
#include "utils.h"

void tty_puts(t_tty *term, const char *s) {
	tty_write(term, s, strlen(s));
}
