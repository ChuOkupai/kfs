#pragma once
#include <stdarg.h>
#include <stddef.h>

#define EOF (-1)

/**
 * Writes formatted output to stdout.
 * @param format A format string.
 * @param ... Arguments to be formatted.
 * @return The number of characters printed, or a negative value if an error occurred.
 */
int printf(const char *format,
	...) __attribute__((format(printf,1,2),nonnull(1)));

/**
 * Writes a character to stdout.
 * @param c The character to write.
 * @return The character written as an unsigned char cast to an int, or EOF on error.
 */
int putchar(int c);

/**
 * Writes a string followed by a newline to stdout.
 * @param s The string to write.
 * @return A non-negative number on success, or EOF on error.
 */
int puts(const char *s);

/**
 * Writes formatted output to a sized buffer.
 * @param str The buffer to write to.
 * @param n The size of the buffer.
 * @param format A format string.
 * @param ... Arguments to be formatted.
 * @return The number of characters that would have been written if n had been sufficiently large,
 *         or a negative value if an error occurred.
 */
int snprintf(char *str, size_t n, const char *format,
	...) __attribute__((format(printf,3,4),nonnull(3)));

/**
 * Writes formatted output to a buffer.
 * @param str The buffer to write to.
 * @param format A format string.
 * @param ... Arguments to be formatted.
 * @return The number of characters written, or a negative value if an error occurred.
 */
int sprintf(char *str, const char *format,
	...) __attribute__((format(printf,2,3),nonnull(2),nonnull(1)));

/**
 * Writes formatted output to stdout using a va_list.
 * @param format A format string.
 * @param ap A va_list of arguments to be formatted.
 * @return The number of characters printed, or a negative value if an error occurred.
 */
int vprintf(const char *format,
	va_list ap) __attribute__((format(printf,1,0),nonnull(1)));

/**
 * Writes formatted output to a sized buffer using a va_list.
 * @param str The buffer to write to.
 * @param n The size of the buffer.
 * @param format A format string.
 * @param ap A va_list of arguments to be formatted.
 * @return The number of characters that would have been written if n had been sufficiently large,
 *         or a negative value if an error occurred.
 */
int vsnprintf(char *str, size_t n, const char *format,
	va_list ap) __attribute__((format(printf,3,0),nonnull(3)));

/**
 * Writes formatted output to a buffer using a va_list.
 * @param str The buffer to write to.
 * @param format A format string.
 * @param ap A va_list of arguments to be formatted.
 * @return The number of characters written, or a negative value if an error occurred.
 */
int vsprintf(char *str, const char *format,
	va_list ap) __attribute__((format(printf,2,0),nonnull(2),nonnull(1)));
