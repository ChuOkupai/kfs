#include <printf.h>
#include <stdio.h>
#include <string.h>

//void pf_print(t_format *f, const char *s, const char *hash) {
//	if (!(f->flags & FLAG_MINUS))
//		pf_putpadding(f);
//	if (f->flags & FLAG_HASH)
//		pf_putstr(f, hash);
//	while (f->precision--)
//		pf_putchar(f, '0');
//	if (f->dsize)
//		pf_putstr(f, s);
//	if ((f->flags & FLAG_MINUS))
//		pf_putpadding(f);
//	++f->s;
//}


void pf_putchar(t_format *f, const char c) {
	if (f->size == EOF || putchar(c) == EOF)
		f->size = EOF;
	else
		++f->size;
}

void pf_padding_prefix(t_format *f) {
	if (!(f->flags & FLAG_MINUS))
		pf_putpadding(f);
}

void pf_padding_suffix(t_format *f) {
	if (f->flags & FLAG_MINUS)
		pf_putpadding(f);
}

void pf_putpadding(t_format *f) {
	while (f->width--)
		pf_putchar(f, f->flags & FLAG_ZERO ? '0' : ' ');
}

void pf_putstr(t_format *f, const char *s) {
	while (*s)
		pf_putchar(f, *s++);
}
