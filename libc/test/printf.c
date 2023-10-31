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
	printf("  1 |%u|\n", 0);
	printf("  2 |%hhu|\n", (unsigned char)UINT8_MAX);
	printf("  3 |%hu|\n", (unsigned short)UINT16_MAX);
	printf("  4 |%u|\n", (unsigned int)UINT32_MAX);
	printf("  5 |%lu|\n", (unsigned long)UINT32_MAX);
	printf("  6 |%llu|\n", (unsigned long long)UINT64_MAX);
	printf("  7 |%5u|\n", 42);
	printf("  8 |%05u|\n", 42);
	printf("  9 |%.u|\n", 0);
	printf(" 10 |%.u|\n", 42);
	printf(" 11 |%.0u|\n", 0);
	printf(" 12 |%.0u|\n", 42);
	printf(" 13 |%.6u|\n", 42);
	printf(" 14 |%.6u|\n", 42);
	printf(" 15 |%8.6u|\n", 42);
	printf(" 16 |%4.6u|\n", 42);

	print_section("%o");
	printf("  1 |%o|\n", 0);
	printf("  2 |%hho|\n", (unsigned char)UINT8_MAX);
	printf("  3 |%ho|\n", (unsigned short)UINT16_MAX);
	printf("  4 |%o|\n", (unsigned int)UINT32_MAX);
	printf("  5 |%lo|\n", (unsigned long)UINT32_MAX);
	printf("  6 |%llo|\n", (unsigned long long)UINT64_MAX);
	printf("  7 |%5o|\n", 42);
	printf("  8 |%05o|\n", 42);
	printf("  9 |%.o|\n", 0);
	printf(" 10 |%.o|\n", 42);
	printf(" 11 |%.0o|\n", 0);
	printf(" 12 |%.0o|\n", 42);
	printf(" 13 |%.6o|\n", 42);
	printf(" 14 |%.6o|\n", 42);
	printf(" 15 |%8.6o|\n", 42);
	printf(" 16 |%4.6o|\n", 42);
	printf(" 17 |%#o|\n", 0);
	printf(" 18 |%#o|\n", 42);
	printf(" 19 |%#.o|\n", 0);
	printf(" 20 |%#.o|\n", 42);
	printf(" 21 |%#8.6o|\n", 42);
	printf(" 22 |%#4.6o|\n", 42);

	print_section("%x");
	printf("  1 |%x|\n", 0);
	printf("  2 |%hhx|\n", (unsigned char)UINT8_MAX);
	printf("  3 |%hx|\n", (unsigned short)UINT16_MAX);
	printf("  4 |%x|\n", (unsigned int)UINT32_MAX);
	printf("  5 |%lx|\n", (unsigned long)UINT32_MAX);
	printf("  6 |%llx|\n", (unsigned long long)UINT64_MAX);
	printf("  7 |%5x|\n", 42);
	printf("  8 |%05x|\n", 42);
	printf("  9 |%.x|\n", 0);
	printf(" 10 |%.x|\n", 42);
	printf(" 11 |%.0x|\n", 0);
	printf(" 12 |%.0x|\n", 42);
	printf(" 13 |%.6x|\n", 42);
	printf(" 14 |%.6x|\n", 42);
	printf(" 15 |%8.6x|\n", 42);
	printf(" 16 |%4.6x|\n", 42);
	printf(" 17 |%#x|\n", 0);
	printf(" 18 |%#x|\n", 42);
	printf(" 19 |%#.x|\n", 0);
	printf(" 20 |%#.x|\n", 42);
	printf(" 21 |%#8.6x|\n", 42);
	printf(" 22 |%#4.6x|\n", 42);

	print_section("%X");
	printf("  1 |%X|\n", 0);
	printf("  2 |%hhX|\n", (unsigned char)UINT8_MAX);
	printf("  3 |%hX|\n", (unsigned short)UINT16_MAX);
	printf("  4 |%X|\n", (unsigned int)UINT32_MAX);
	printf("  5 |%lX|\n", (unsigned long)UINT32_MAX);
	printf("  6 |%llX|\n", (unsigned long long)UINT64_MAX);
	printf("  7 |%5X|\n", 42);
	printf("  8 |%05X|\n", 42);
	printf("  9 |%.X|\n", 0);
	printf(" 10 |%.X|\n", 42);
	printf(" 11 |%.0X|\n", 0);
	printf(" 12 |%.0X|\n", 42);
	printf(" 13 |%.6X|\n", 42);
	printf(" 14 |%.6X|\n", 42);
	printf(" 15 |%8.6X|\n", 42);
	printf(" 16 |%4.6X|\n", 42);
	printf(" 17 |%#X|\n", 0);
	printf(" 18 |%#X|\n", 42);
	printf(" 19 |%#.X|\n", 0);
	printf(" 20 |%#.X|\n", 42);
	printf(" 21 |%#8.6X|\n", 42);
	printf(" 22 |%#4.6X|\n", 42);

	print_section("%c");
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

	print_section("%p");
	printf(" 1 |%p|\n", NULL);
	printf(" 2 |%p|\n", (void *)0xc0ffee);
	printf(" 2 |%p|\n", (void *)0xdeadbeef);

	print_section("%n");
	int n = -1;
	printf(" 1 %n", &n);
	printf(" -> |%d|\n", n);

	print_section("%%");
	printf(" 1 |%%|\n");
}
