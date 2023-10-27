#include <ctype.h>
#include <printf.h>
#include <stdio.h>
#include <string.h>

// Avoid undefined reference to `__udivmoddi4' error with GCC
static inline void divmod(t_ull n, t_ull d, t_ull *q, t_ull *r) {
	t_ull qn = 0, qd = 1;
	while ((t_ll)d >= 0 && d < n) {
		d <<= 1;
		qd <<= 1;
	}
	while (qd) {
		if (n >= d) {
			n -= d;
			qn += qd;
		}
		d >>= 1;
		qd >>= 1;
	}
	*q = qn;
	*r = n;
}

static inline int max_int(int a, int b) {
	return a > b ? a : b;
}

static inline int min_int(int a, int b) {
	return a < b ? a : b;
}

static char *num_to_string(t_ull n, int base) {
	static char	buf[PF_CONVERT_BUFSIZE];
	const char	*b16 = "0123456789abcdef";
	char		*d;

	d = buf + sizeof(buf);
	*--d = '\0';
	if (!n)
		*--d = '0';
	while (n) {
		t_ull r;
		divmod(n, base, &n, &r);
		*--d = b16[r];
	}
	return d;
}

static const char *parse_int(int *i, const char *s) {
	int n = 0;
	while (isdigit(*s))
		n = 10 * n + *s++ - '0';
	*i = n;
	return s;
}

static inline const char *parse_flags(t_flags *f, const char *s) {
	const char *flags = "#0- +";
	*f = 0;
	while (strchr(flags, *s))
		*f |= 1 << (*s++ - *flags);
	return s;
}

static inline const char *parse_width(int *w, t_flags *f, const char *s, va_list l) {
	*w = 0;
	if (*s == '*') {
		*w = va_arg(l, int);
		++s;
		if (*w < 0) {
			*w = -*w;
			*f |= FLAG_MINUS;
		}
	}
	else
		s = parse_int(w, s);
	return s;
}

static inline const char *parse_precision(int *p, const char *s, va_list l) {
	if (*s == '.') {
		*p = 0;
		++s;
		if (*s == '*') {
			*p = va_arg(l, int);
			++s;
			if (*p < 0)
				*p = -1;
		}
		else if (isdigit(*s))
			s = parse_int(p, s);
	} else
		*p = -1;
	return s;
}

static inline const char *parse_modifier(t_modifier *m, const char *s) {
	static const char *modifiers[] = { "hh", "h", "l", "ll", "j", "z", "t" };
	*m = 0;
	for (size_t i = 0; i < sizeof(modifiers) / sizeof(*modifiers); ++i)
		if (!strncmp(s, modifiers[i], strlen(modifiers[i]))) {
			*m |= 1 << i;
			return s + strlen(modifiers[i]);
		}
	return s;
}

static inline const char *parse_directives(t_format *f, const char *s, va_list l) {
	s = parse_flags(&f->flags, s);
	s = parse_width(&f->width, &f->flags, s, l);
	s = parse_precision(&f->precision, s, l);
	s = parse_modifier(&f->modifier, s);
	return s;
}

static inline void parse_c(t_format *f, va_list l) {
	unsigned char c = va_arg(l, int);
	f->width = max_int(f->width - 1, 0);
	pf_padding_prefix(f);
	pf_putchar(f, c);
	pf_padding_suffix(f);
}

static inline void parse_s(t_format *f, const char *s) {
	if (!s)
		s = "(null)";
	int n = strlen(s);
	if (f->precision >= 0)
		n = min_int(n, f->precision);
	f->width = max_int(f->width - n, 0);
	pf_padding_prefix(f);
	while (n--)
		pf_putchar(f, *s++);
	pf_padding_suffix(f);
}

static inline void parse_numeric(t_format *f, const char c) {
	
}

int __parse_format(const char *s, va_list l) {
	t_format f = { 0 };
	while (*s && f.size != EOF)
		if (*s != '%' || *++s == '%')
			pf_putchar(&f, *s++);
		else {
			s = parse_directives(&f, s, l);
			if ((f.flags & FLAG_MINUS) || f.precision >= 0)
				f.flags &= ~FLAG_ZERO;
			if (f.flags & FLAG_PLUS)
				f.flags &= ~FLAG_SPACE;
			if (*s == 'c')
				parse_c(&f, l);
			else if (*s == 's')
				parse_s(&f, va_arg(l, char*));
			else if (strchr("diouxX", *s))
				parse_numeric(&f, *s);
			//else if (*s == 'd' || *s == 'i')
			//	pf_parse_d(f, pf_va_arg(flags, l));
			//else if (*s == 'u')
			//	pf_parse_u(f, pf_va_arg_unsigned(flags, l));
			//else if (*s == 'x' || *s == 'X')
			//	pf_parse_x(f, pf_va_arg_unsigned(flags, l));
			//else if (*s == 'o')
			//	pf_parse_o(f, pf_va_arg_unsigned(flags, l));
			//else if (*s == 'p')
			//	pf_parse_p(f, (uint32_t)((void*)va_arg(l, void*)));
			//else if (*s == 'n')
			//	pf_parse_n(f, va_arg(l, int64_t*));
			else
				continue;
			++s;
		}
	return f.size;
}
