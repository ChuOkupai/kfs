#include <stdio.h>

int main() {
	puts("Test - no directives");
	printf("This is a test\n");

	puts("Test - %%");
	printf("|%%|\n");

	puts("Test - %c");
	printf("|%c|\n", 'a');
	printf("|%2c|\n", 'b');
	printf("|%-3c|\n", 'c');
	printf("|%*c|\n", -4, 'd');

	puts("Test - %s");
	printf("|%s|\n", "foo");
	printf("|%10s|\n", "bar");
	printf("|%-10s|\n", "baz");
	printf("|%*s|\n", -10, "qux");
	printf("|%.*s|\n", -10, "qux");
	printf("|%*.*s|\n", -10, 3, "qux");
	printf("|%.0s|\n", "foo");
	printf("|%.3s|\n", "ab");
	printf("|%.3s|\n", "abcde");
	printf("|%4.3s|\n", "abcdef");
	printf("|%4.5s|\n", "abcdef");
	printf("|%4.7s|\n", "abcdef");
	printf("|%8.3s|\n", "abcdef");
	printf("|%8.5s|\n", "abcdef");
	printf("|%8.7s|\n", "abcdef");
	printf("|%-10.3s|\n", "abcdef");
}
