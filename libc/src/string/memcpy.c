#include <stddef.h>

void *memcpy(void *dest, const void *srcp, size_t n) {
	unsigned char		*dst;
	const unsigned char	*src = (const unsigned char*) srcp;

	dst = (unsigned char *) dest;
	for (size_t i = 0; i < n; i++)
		dst[i] = src[i];
	return dest;
}
