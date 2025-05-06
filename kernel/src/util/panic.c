#include <panic.h>
#include <panic_utils.h>
#include <stdio.h>
#include <stdarg.h>
#include <tty.h>
#include <stack.h>

void panic(const char *format, ...)
{
	// Disable interrupts
	asm volatile("cli");

	printf("\n\n*** KERNEL PANIC ***\n");
	print_stack_info();
	print_stack_trace();

	va_list ap;
	va_start(ap, format);
	if (format) {
		vprintf(format, ap);
		printf("\n");
	}
	va_end(ap);

	save_stack_pointer();
	halt_cpu();
}