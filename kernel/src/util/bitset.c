#include <bitset.h>

size_t bitset_is_set(const t_bitset *b, size_t i)
{
	return b[i / BIT_SIZEOF(size_t)] & (((size_t)1) << (i % BIT_SIZEOF(size_t)));
}

void bitset_set(t_bitset *b, size_t i)
{
	b[i / BIT_SIZEOF(size_t)] |= (((size_t)1) << (i % BIT_SIZEOF(size_t)));
}

void bitset_unset(t_bitset *b, size_t i)
{
	b[i / BIT_SIZEOF(size_t)] &= ~(((size_t)1) << (i % BIT_SIZEOF(size_t)));
}
