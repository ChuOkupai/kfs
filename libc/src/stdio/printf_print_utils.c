#include <printf.h>
#include <stdio.h>
#include <string.h>

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
