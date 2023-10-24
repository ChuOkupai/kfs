#pragma once
#include <stddef.h>
#include <macros.h>

/** A memory-efficient representation of an array of bits. */
typedef size_t t_bitset;

#define BITSET_SIZE(n) (n / BIT_SIZEOF(size_t) + ((n % BIT_SIZEOF(size_t)) != 0))

/**
 * Checks if a bit is set in a bitset.
 * @param b The bitset.
 * @param i The index of the bit to check.
 * @return A non zero value if the bit at index i is set, 0 otherwise.
 */
size_t bitset_is_set(const t_bitset *b, size_t i);

/**
 * Sets a bit in a bitset.
 * @param b The bitset.
 * @param i The index of the bit to set.
 */
void bitset_set(t_bitset *b, size_t i);

/**
 * Unsets a bit in a bitset.
 * @param b The bitset.
 * @param i The index of the bit to unset.
 */
void bitset_unset(t_bitset *b, size_t i);
