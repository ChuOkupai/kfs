#include <string.h>
#include "tty.h"
<<<<<<< HEAD:kernel/kernel/src/tty/tty_puts.c
#include "utils.h"
#include "string.h"
=======
>>>>>>> 05f7bbd (Fix kernel build):kernel/src/tty/tty_puts.c

void tty_puts(const char *s) {
	tty_write(s, strlen(s));
}
