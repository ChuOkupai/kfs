#include <ctype.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>

static unsigned long next_value(unsigned long c, unsigned long base) {
	if (isdigit(c))
		c -= '0';
	else
		c = isalpha(c) ? (unsigned long)tolower(c) - 'a' + 10 : base;
	return c;
}

static long check_limit(unsigned long c, unsigned long n, unsigned long cutoff, unsigned long cutlim) {
	return n > cutoff || (n == cutoff && c > cutlim) ? -1 : 1;
}

static unsigned long check_result(unsigned long n, long lim, int neg) {
	if (!lim)
		errno = EINVAL;
	else if (lim < 0) {
		errno = ERANGE;
		n = ULONG_MAX;
	}
	else if (neg)
		n = -n;
	return n;
}

static unsigned long parse(const char *s, const char **end, unsigned long base, int neg) {
	unsigned long	cutoff;
	unsigned long	cutlim;
	unsigned long	c;
	unsigned long	n;
	long			lim;

	cutoff = (unsigned long)ULONG_MAX / base;
	cutlim = (unsigned long)ULONG_MAX % base;
	lim = 0;
	n = 0;
	while ((c = next_value(*s++, base)) < base)
		if (lim >= 0 && (lim = check_limit(c, n, cutoff, cutlim)))
			n = n * base + c;
	*end = lim ? s - 1 : NULL;
	return check_result(n, lim, neg);
}

unsigned long strtoul(const char *str, char **endptr, int base) {
	const char		*s;
	int				neg;
	unsigned long	n;

	s = str;
	while (isspace(*s))
		++s;
	if ((neg = *s == '-') || *s == '+')
		++s;
	if ((!base || base == 16) && *s == '0' && (s[1] == 'x' || s[1] == 'X')) {
		str = s + 1;
		s += 2;
		base = 16;
	}
	else if (!base)
		base = *s == '0' ? 8 : 10;
	n = parse(s, &s, base, neg);
	if (endptr)
		*endptr = (char *)(s ? s : str);
	return n;
}
