#include <stddef.h>

void *memset(void *s, int c, size_t n) {
	unsigned char	*buf;

	buf = (unsigned char *)s;
	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char) c;
	return (s);
}
