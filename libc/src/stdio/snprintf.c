#include <stdarg.h>
#include <stdio.h>

int snprintf(char *str, size_t n, const char *format, ...) {
	va_list	l;
	int		size;

	va_start(l, format);
	size = vsnprintf(str, n, format, l);
	va_end(l);
	return size;
}
