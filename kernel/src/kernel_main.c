#include <boot.h>
#include <shell.h>
#include <panic.h>
#include <stdio.h>

#if !defined(__i386__)
# error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

#include <stack.h>

void kernel_main() {
	run_boot_seq();

	// int a = 1, b = 0;
	// int c = a/b;

	// printf("This should not be printed: %d\n", c);
	shell_run();
}
