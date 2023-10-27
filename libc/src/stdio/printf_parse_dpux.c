#include <ctype.h>
#include <printf.h>

static void	pf_set_fields(t_format *f, int hlen) {
	if (f->precision >= 0 || (f->flags & FLAG_MINUS))
		f->flags &= ~FLAG_ZERO;
	if ((f->precision = f->precision - f->dsize) < 0)
		f->precision = 0;
	hlen = f->dsize + f->precision + (((f->flags & FLAG_HASH)) ? hlen : 0);
	if ((f->width = f->width - hlen) < 0)
		f->width = 0;
	if ((f->flags & FLAG_ZERO)) {
		f->precision = f->width;
		f->width = 0;
	}
}

void		pf_parse_d(t_format *f, int64_t n) {
	const char	*h;
	const char	*s;

	s = pf_convert(f, (n < 0 ? -n : n), 10);
	if (n < 0)
		h = "-";
	else if ((f->flags & FLAG_PLUS))
		h = "+";
	else
		h = (f->flags & FLAG_SPACE) ? " " : 0;
	if (h)
		f->flags |= FLAG_HASH;
	else
		f->flags &= ~FLAG_HASH;
	pf_set_fields(f, 1);
	pf_print(f, s, h);
}

void		pf_parse_p(t_format *f, uint64_t n) {
	const char *s;

	f->flags |= MODIFIER_LL;
	s = pf_convert(f, n, 16);
	f->flags |= FLAG_HASH;
	pf_set_fields(f, 2);
	pf_print(f, s, "0x");
}

void		pf_parse_u(t_format *f, uint64_t n) {
	const char *s;

	s = pf_convert(f, n, 10);
	pf_set_fields(f, 0);
	pf_print(f, s, 0);
}

void		pf_parse_x(t_format *f, uint64_t n) {
	char *s;

	s = pf_convert(f, n, 16);
	if (*f->s == 'X')
		for (int i = 0; s[i]; ++i)
			s[i] = toupper(s[i]);
	if (!n && (f->flags & FLAG_HASH))
		f->flags &= ~FLAG_HASH;
	pf_set_fields(f, 2);
	pf_print(f, s, (*f->s == 'x') ? "0x" : "0X");
}
