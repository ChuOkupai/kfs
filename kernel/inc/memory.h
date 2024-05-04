#pragma once
#include <stddef.h>
#include <stdint.h>

/**
 * Print a memory dump of the given address.
 * @param addr The address to dump.
 * @param size The size of the memory to dump.
*/
void hexdump(const void *addr, size_t size);
