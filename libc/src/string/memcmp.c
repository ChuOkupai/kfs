#include <stddef.h>

int memcmp(const void *dest, const void *src, size_t n) {
	const unsigned char	*a = (const unsigned char*) dest;
	const unsigned char	*b = (const unsigned char*) src;

	for (size_t i = 0; i < n; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}
