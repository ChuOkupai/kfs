#pragma once
#include <stddef.h>

void abort();

void *bsearch(const void *key, const void *base, size_t nmemb,
	size_t size, int (*compar)(const void *, const void *));

int rand();

void srand(unsigned int seed);

unsigned long strtoul(const char *nptr, char **endptr, int base);
