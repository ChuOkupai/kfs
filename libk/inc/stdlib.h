#pragma once
#include <stddef.h>

/**
 * Causes abnormal program termination.
 */
void abort();

/**
 * Binary search in a sorted array.
 * @param key The key to search for.
 * @param base Pointer to the first element of the array.
 * @param nmemb Number of elements in the array.
 * @param size Size of each element in the array.
 * @param compar Comparison function that returns negative if first arg is less than second,
 *               zero if they are equal, positive if first arg is greater than second.
 * @return Pointer to the matching element, or NULL if not found.
 */
void *bsearch(const void *key, const void *base, size_t nmemb,
	size_t size, int (*compar)(const void *, const void *));

/**
 * Returns a pseudo-random integer.
 * @return A pseudo-random integer.
 */
int rand();

/**
 * Seeds the random number generator.
 * @param seed The seed value.
 */
void srand(unsigned int seed);

/**
 * Converts a string to an unsigned long integer.
 * @param nptr The string to convert.
 * @param endptr If not NULL, stores the address of the first invalid character.
 * @param base The base to use for the conversion (between 2 and 36, or 0).
 * @return The converted value.
 */
unsigned long strtoul(const char *nptr, char **endptr, int base);
