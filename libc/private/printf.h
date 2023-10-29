#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define PF_CONVERT_BUFSIZE 64

typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef enum e_flags
{
	FLAG_HASH = 0x1,
	FLAG_ZERO = 0x2,
	FLAG_MINUS = 0x4,
	FLAG_SPACE = 0x8,
	FLAG_PLUS = 0x10
}	t_flags;

typedef enum e_modifier {
	MODIFIER_HH = 0x1,
	MODIFIER_H = 0x2,
	MODIFIER_LL = 0x4,
	MODIFIER_L = 0x8,
	MODIFIER_J = 0x10,
	MODIFIER_Z = 0x20,
	MODIFIER_T = 0x40
}	t_modifier;

typedef struct s_format
{
	// Input control
	va_list		args;

	// Format directives
	t_flags		flags;
	int			width;
	int			precision;
	t_modifier	modifier;

	// Output control
	const char	*output_str;
	long		output_size;
	int			size;
}	t_format;

int		__parse_format(const char *s, va_list l);

void		pf_padding_prefix(t_format *f);

void		pf_padding_suffix(t_format *f);

void		pf_putchar(t_format *f, const char c);

void		pf_putpadding(t_format *f);

void		pf_putchar(t_format *f, const char c);

void		pf_putstr(t_format *f, const char *s);
