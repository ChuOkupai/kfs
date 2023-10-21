#include <tty.h>

void tty_write(const char *data, size_t size) {
	for (size_t i = 0; i < size; ++i)
		tty_putc(data[i]);
}
