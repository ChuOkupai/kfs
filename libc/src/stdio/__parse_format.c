#include <sys/types.h>
#include <ctype.h>
#include <printf.h>
#include <stdio.h>
#include <string.h>

static inline int max_int(int a, int b) {
	return a > b ? a : b;
}

static inline int min_int(int a, int b) {
	return a < b ? a : b;
}

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

static inline const char *parse_flags(t_format *f, const char *s) {
	const char *flags = "#0- +";
	char *i;
	f->flags = 0;
	while ((i = strchr(flags, *s)))
		f->flags |= 1 << (i - flags), ++s;
	return s;
}

static inline const char *parse_width(t_format *f, const char *s) {
	f->width = 0;
	if (*s == '*') {
		f->width = va_arg(f->args, int);
		++s;
		if (f->width < 0) {
			f->width = -f->width;
			f->flags |= FLAG_MINUS;
		}
	}
	else
		s = parse_int(&f->width, s);
	return s;
}

static inline const char *parse_precision(t_format *f, const char *s) {
	if (*s == '.') {
		if (*(++s) == '*') {
			f->precision = va_arg(f->args, int);
			++s;
			if (f->precision < 0)
				f->precision = -1;
		}
		else
			s = parse_int(&f->precision, s);
	} else
		f->precision = -1;
	return s;
}

static inline const char *parse_modifier(t_format *f, const char *s) {
	static const char *modifiers[] = { "hh", "h", "ll", "l", "j", "z", "t" };
	f->modifier = 0;
	for (size_t i = 0; i < sizeof(modifiers) / sizeof(*modifiers); ++i)
		if (!strncmp(s, modifiers[i], strlen(modifiers[i]))) {
			f->modifier = 1 << i;
			return s + strlen(modifiers[i]);
		}
	return s;
}

static inline const char *parse_directives(t_format *f, const char *s) {
	s = parse_flags(f, s);
	s = parse_width(f, s);
	s = parse_precision(f, s);
	s = parse_modifier(f, s);
	return s;
}

static inline t_ll extract_signed_numeric(t_modifier m, va_list *l) {
	t_ll n;
	if (m & MODIFIER_LL)
		n = va_arg(*l, t_ll);
	else if (m & MODIFIER_L)
		n = va_arg(*l, long);
	else if (m & MODIFIER_HH)
		n = (char)va_arg(*l, int);
	else if (m & MODIFIER_H)
		n = (short)va_arg(*l, int);
	else if (m & MODIFIER_J)
		n = va_arg(*l, intmax_t);
	else if (m & MODIFIER_Z)
		n = va_arg(*l, ssize_t);
	else if (m & MODIFIER_T)
		n = va_arg(*l, ptrdiff_t);
	else
		n = va_arg(*l, int);
	return n;
}

static inline void print_sign(t_format *f, t_ll n) {
	if (n < 0)
		pf_putchar(f, '-');
	else if (f->flags & FLAG_PLUS)
		pf_putchar(f, '+');
	else if (f->flags & FLAG_SPACE)
		pf_putchar(f, ' ');
}

static inline void print_signed_numeric(t_format *f) {
	t_ll n = extract_signed_numeric(f->modifier, &f->args);
	char *b = num_to_string(n < 0 ? -n : n, 10);
	int sign = n < 0 || (f->flags & (FLAG_PLUS | FLAG_SPACE));
	int length = strlen(b);
	if (!f->precision && !n)
		b = "";
	f->precision = max_int(f->precision - length, 0);
	f->width = max_int(f->width - f->precision - length - sign, 0);
	if (f->flags & FLAG_ZERO)
		print_sign(f, n);
	pf_padding_prefix(f);
	if (!(f->flags & FLAG_ZERO))
		print_sign(f, n);
	while (f->precision--)
		pf_putchar(f, '0');
	pf_putstr(f, b);
	pf_padding_suffix(f);
}

static inline t_ull extract_unsigned_numeric(t_modifier m, va_list *l) {
	t_ull n;
	if (m & MODIFIER_LL)
		n = va_arg(*l, t_ull);
	else if (m & MODIFIER_L)
		n = va_arg(*l, unsigned long);
	else if (m & MODIFIER_HH)
		n = (unsigned char)va_arg(*l, unsigned int);
	else if (m & MODIFIER_H)
		n = (unsigned short)va_arg(*l, unsigned int);
	else if (m & MODIFIER_J)
		n = va_arg(*l, uintmax_t);
	else if (m & MODIFIER_Z)
		n = va_arg(*l, size_t);
	else if (m & MODIFIER_T)
		n = va_arg(*l, ptrdiff_t);
	else
		n = va_arg(*l, unsigned int);
	return n;
}

static inline void print_unsigned_numeric(t_format *f, const char c) {
	t_ull n = extract_unsigned_numeric(f->modifier, &f->args);
	const int base = tolower(c) == 'x' ? 16 : (c == 'o' ? 8 : 10);
	char *b = num_to_string(n, base);
	int length = strlen(b);
	if (c == 'X')
		for (int i = 0; i < length; ++i)
			b[i] = toupper(b[i]);
	f->precision = max_int(f->precision - length, 0);
	if (!f->precision && !n)
		b = "";
	f->width = max_int(f->width - f->precision - length, 0);
	pf_padding_prefix(f);
	while (f->precision--)
		pf_putchar(f, '0');
	pf_putstr(f, b);
	pf_padding_suffix(f);
}

static inline void print_char(t_format *f) {
	unsigned char c = va_arg(f->args, int);
	f->width = max_int(f->width - 1, 0);
	pf_padding_prefix(f);
	pf_putchar(f, c);
	pf_padding_suffix(f);
}

static inline void print_str(t_format *f, const char *s) {
	if (!s)
		s = "(null)";
	int length = strlen(s);
	if (f->precision >= 0)
		length = min_int(length, f->precision);
	f->width = max_int(f->width - length, 0);
	pf_padding_prefix(f);
	while (length--)
		pf_putchar(f, *s++);
	pf_padding_suffix(f);
}

static inline void print_pointer(t_format *f) {
	f->flags |= FLAG_HASH;
	f->modifier |= MODIFIER_L;
	print_unsigned_numeric(f, 'x');
}

static inline void store_written(t_format *f) {
	int *n = va_arg(f->args, int*);
	*n = f->size;
}

int __parse_format(const char *s, va_list l) {
	t_format f = { 0 };
	va_copy(f.args, l);
	while (*s && f.size != EOF)
		if (*s != '%' || *++s == '%')
			pf_putchar(&f, *s++);
		else {
			s = parse_directives(&f, s);
			if ((f.flags & FLAG_MINUS) || f.precision >= 0)
				f.flags &= ~FLAG_ZERO;
			if (f.flags & FLAG_PLUS)
				f.flags &= ~FLAG_SPACE;
			if (strchr("di", *s))
				print_signed_numeric(&f);
			else if (strchr("ouxX", *s))
				print_unsigned_numeric(&f, *s);
			else if (*s == 'c')
				print_char(&f);
			else if (*s == 's')
				print_str(&f, va_arg(f.args, char*));
			else if (*s == 'p')
				print_pointer(&f);
			else if (*s == 'n')
				store_written(&f);
			else
				continue;
			++s;
		}
	return f.size;
}
