#include "tty.h"
#include "utils.h"
#include "string.h"

void tty_puts(const char *s) {
	tty_write(s, strlen(s));
}
