#pragma once
#include <stddef.h>

int		memcmp(const void *aptr, const void *bptr, size_t n);
void	*memcpy(void *dest, const void *src, size_t n);
void	*memmove(void *dest, const void *src, size_t n);
void	*memset(void *s, int c, size_t n);
size_t	strlen(const char *s);
