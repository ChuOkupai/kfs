#include <stdarg.h>
#include <stdio.h>

int sprintf(char *str, const char *format, ...) {
	va_list	l;
	int		size;

	va_start(l, format);
	size = vsprintf(str, format, l);
	va_end(l);
	return size;
}
