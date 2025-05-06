#pragma once
#include <stddef.h>

/**
 * Compares memory areas.
 * @param aptr Pointer to the first memory area.
 * @param bptr Pointer to the second memory area.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if aptr is found to be
 *         less than, equal to, or greater than bptr.
 */
int memcmp(const void *aptr, const void *bptr, size_t n);

/**
 * Copies memory area.
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return A pointer to the destination memory area.
 */
void *memcpy(void *dest, const void *src, size_t n);

/**
 * Copies memory area, handling overlapping memory correctly.
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return A pointer to the destination memory area.
 */
void *memmove(void *dest, const void *src, size_t n);

/**
 * Fills memory with a constant byte.
 * @param s Pointer to the memory area to fill.
 * @param c Byte to fill the memory area with.
 * @param n Number of bytes to fill.
 * @return A pointer to the memory area.
 */
void *memset(void *s, int c, size_t n);

/**
 * Locates the first occurrence of a character in a string.
 * @param s Pointer to the string to search.
 * @param c Character to search for.
 * @return Pointer to the first occurrence of c in s, or NULL if not found.
 */
char *strchr(const char *s, int c);

/**
 * Compares two strings.
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @return An integer less than, equal to, or greater than zero if s1 is found to be
 *         less than, equal to, or greater than s2.
 */
int strcmp(const char *s1, const char *s2);

/**
 * Calculates the length of a string.
 * @param s Pointer to the string.
 * @return The number of bytes in the string before the terminating null byte.
 */
size_t strlen(const char *s);

/**
 * Compares two strings, limited by n bytes.
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @param n Maximum number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if s1 is found to be
 *         less than, equal to, or greater than s2.
 */
int strncmp(const char *s1, const char *s2, size_t n);
