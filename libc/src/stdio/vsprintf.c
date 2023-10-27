#include <printf.h>

int vsprintf(char *str, const char *format, va_list ap) {
	*str = '\0';
	return __parse_format(format, ap);
}
