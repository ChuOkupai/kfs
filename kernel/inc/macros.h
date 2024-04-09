#pragma once
#include <limits.h>

/**
 * Gets the absolute value of a number.
 * @param X The number.
 * @return The absolute value of X.
 */
#define ABS(X) ((X) < ((typeof(X))0) ? -(X) : (X))

/**
 * Gets the size in bits instead of bytes.
 * @param N The number of bytes.
 * @return The size in bits of N bytes.
 */
#define BIT_SIZEOF(N) (sizeof(N) * CHAR_BIT)

/**
 * Gets the maximum of two values.
 * @param A The first value.
 * @param B The second value.
 * @return The maximum of A and B.
 */
#define MAX(A, B) ((A) > (B) ? (A) : (B))

/**
 * Gets the size of a static array.
 * @param A The array.
 * @return The size of the array.
 */
#define SIZEOF_ARRAY(A) (sizeof(A) / sizeof(*(A)))
