#include <string.h>
#include <tty.h>

void tty_puts(const char *s) {
	tty_write(s, strlen(s));
}
