#include "stdlib.h"
#include <stddef.h>

void *bsearch(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
	const char *base = (const char *) base0;
	int 		lim;
	int			cmp;
	const void	*p;

	for (lim = nmemb; lim != 0; lim >>= 1)
	{
		p = base + (lim >> 1) * size;
		cmp = (*compar)(key, p);
		if (cmp == 0)
			return (void *)p;
		if (cmp > 0)
		{
			base = (const char *)p + size;
			lim--;
		}
	}
	return (NULL);
}