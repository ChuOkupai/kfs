#include <string.h>
#include <printf.h>

void		pf_parse_n(t_format *f, int64_t *size) {
	f->s++;
	if (!size)
		return ;
	if ((f->length_mod & MODIFIER_LL))
		*((long long*)size) = f->size;
	else if ((f->length_mod & MODIFIER_L))
		*((long*)size) = f->size;
	else if ((f->length_mod & MODIFIER_HH))
		*((char*)size) = (char)f->size;
	else if ((f->length_mod & MODIFIER_H))
		*((short*)size) = (short)f->size;
	else
		*((int*)size) = f->size;
}

void		pf_parse_o(t_format *f, uint64_t n) {
	const char	*s;
	int			t;

	s = pf_convert(f, n, 8);
	if (!n && (f->flags & FLAG_HASH) && f->precision)
		f->flags &= ~FLAG_HASH;
	if (f->precision >= 0 || (f->flags & FLAG_MINUS))
		f->flags &= ~FLAG_ZERO;
	t = f->dsize + ((f->flags & FLAG_HASH) != 0);
	if ((f->precision = f->precision - t) < 0)
		f->precision = 0;
	if ((f->width = f->width - t - f->precision) < 0)
		f->width = 0;
	pf_print(f, s, "0");
}
