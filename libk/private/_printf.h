#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define PF_CONVERT_BUFSIZE 64

typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef enum e_flags {
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

typedef struct s_format {
	// Input control
	va_list		args;

	// Format directives
	t_flags		flags;
	int			width;
	int			precision;
	t_modifier	modifier;

	// Output control
	char		*output_str;
	int			has_max_size;
	size_t		max_size;
	int			size;
}	t_format;

/**
 * Internal printf format parser.
 * @param s The format string to parse.
 * @param l The va_list containing arguments to format.
 * @return The number of characters printed, or a negative value if an error occurred.
 */
int __parse_format(const char *s, va_list l);

/**
 * Internal printf format parser that writes to a string.
 * @param dst The destination buffer.
 * @param s The format string to parse.
 * @param l The va_list containing arguments to format.
 * @return The number of characters written, or a negative value if an error occurred.
 */
int __parse_format_str(char *dst, const char *s, va_list l);

/**
 * Internal printf format parser that writes to a sized buffer.
 * @param dst The destination buffer.
 * @param n The size of the destination buffer.
 * @param s The format string to parse.
 * @param l The va_list containing arguments to format.
 * @return The number of characters that would have been written if n had been sufficiently large,
 *         or a negative value if an error occurred.
 */
int __parse_format_nstr(char *dst, size_t n, const char *s, va_list l);
