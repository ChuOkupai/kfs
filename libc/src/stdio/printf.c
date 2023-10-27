#include <stdio.h>

int printf(const char *format, ...) {
	va_list	l;
	int		n;

	va_start(l, format);
	n = vprintf(format, l);
	va_end(l);
	return n;
}
