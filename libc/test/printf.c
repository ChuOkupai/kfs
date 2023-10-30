#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void print_sep(size_t n) {
	putchar('+');
	for (size_t i = 1; i < n - 1; ++i)
		putchar('-');
	puts("+");
}

static void print_str(const char *s) {
	for (size_t i = 0; s[i]; ++i)
		putchar(s[i]);
}

static void print_section(const char *section) {
	const char *label = "| > Test - ";
	const size_t n = strlen(label) + strlen(section) + 2;
	print_sep(n);
	print_str(label);
	print_str(section);
	puts(" |");
	print_sep(n);
}

int main() {
	print_section("no directives");
	printf(" 1 |This is a test|\n");

	print_section("%d");
	printf("  1 |%d|\n", 0);
	printf("  2 |%hhd|\n", (char)INT8_MIN);
	printf("  3 |%hhd|\n", (char)INT8_MAX);
	printf("  4 |%hd|\n", (short)INT16_MIN);
	printf("  5 |%hd|\n", (short)INT16_MAX);
	printf("  6 |%d|\n", (int)INT32_MIN);
	printf("  7 |%d|\n", (int)INT32_MAX);
	printf("  8 |%ld|\n", (long)INT32_MIN);
	printf("  9 |%ld|\n", (long)INT32_MAX);
	printf(" 10 |%lld|\n", (long long)INT64_MIN);
	printf(" 11 |%lld|\n", (long long)INT64_MAX);
	printf(" 12 |%5d|\n", 42);
	printf(" 13 |%05d|\n", 42);
	printf(" 14 |%-5d|\n", -42);
	printf(" 15 |%-5d|\n", 42);
	printf(" 16 |%+5d|\n", 42);
	printf(" 17 |%+05d|\n", -42);
	printf(" 18 |%+05d|\n", 42);
	printf(" 19 |%+05d|\n", 0);
	printf(" 20 |% 05d|\n", -42);
	printf(" 21 |% 05d|\n", 42);
	printf(" 22 |% 05d|\n", 0);
	printf(" 23 |% d|\n", -42);
	printf(" 24 |% d|\n", 0);
	printf(" 25 |% d|\n", 42);
	printf(" 26 |%.d|\n", 0);
	printf(" 27 |%.d|\n", 42);
	printf(" 28 |%.0d|\n", 0);
	printf(" 29 |%.0d|\n", 42);
	printf(" 30 |%.6d|\n", 42);
	printf(" 31 |%.6d|\n", -42);
	printf(" 32 |%8.6d|\n", -42);
	printf(" 33 |%4.6d|\n", -42);
	printf(" 34 |% .6d|\n", 42);
	printf(" 35 |% .6d|\n", -42);
	printf(" 36 |% 8.6d|\n", -42);
	printf(" 37 |% 4.6d|\n", -42);

	print_section("%u");
	printf(" 1 |%c|\n", 'a');
	printf(" 2 |%2c|\n", 'b');
	printf(" 3 |%-3c|\n", 'c');
	printf(" 4 |%*c|\n", -4, 'd');

	print_section("%s");
	printf("  1 |%s|\n", "foo");
	printf("  2 |%10s|\n", "bar");
	printf("  3 |%-10s|\n", "baz");
	printf("  4 |%*s|\n", -10, "qux");
	printf("  5 |%.*s|\n", -10, "qux");
	printf("  6 |%*.*s|\n", -10, 3, "qux");
	printf("  7 |%.0s|\n", "foo");
	printf("  8 |%.3s|\n", "ab");
	printf("  9 |%.3s|\n", "abcde");
	printf(" 10 |%4.3s|\n", "abcdef");
	printf(" 11 |%4.5s|\n", "abcdef");
	printf(" 12 |%4.7s|\n", "abcdef");
	printf(" 13 |%8.3s|\n", "abcdef");
	printf(" 14 |%8.5s|\n", "abcdef");
	printf(" 15 |%8.7s|\n", "abcdef");
	printf(" 16 |%-10.3s|\n", "abcdef");

	print_section("%%");
	printf(" 1 |%%|\n");
}
