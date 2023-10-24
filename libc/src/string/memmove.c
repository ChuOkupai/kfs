#include <stddef.h>

void *memmove(void *dest, const void *srcp, size_t size)
{
	unsigned char			*dst;
	const unsigned char		*src = (const unsigned char *) srcp;

	dst = (unsigned char *) dest;
	if (dst < src) {
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
	else {
		for (size_t i = size; i != 0; i--)
			dst[i - 1] = src[i - 1];
	}
	return (dest);
}
