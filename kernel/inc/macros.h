#pragma once
#include <limits.h>

/**
 * Gets the size in bits instead of bytes.
 * @param N The number of bytes.
 * @return The size in bits of N bytes.
 */
#define BIT_SIZEOF(N) (sizeof(N) * CHAR_BIT)
