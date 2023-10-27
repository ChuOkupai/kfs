#include <printf.h>

int vsnprintf(char *str, size_t n, const char *format, va_list ap) {
	if (n)
		*str = '\0';
	return __parse_format(format, ap);
}
