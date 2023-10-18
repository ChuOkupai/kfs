#include <stdint.h>
#include "utils.h"
#include "terminal.h"

#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
# error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main()
{
	t_terminal buf;
	terminal_init(&buf);
	terminal_puts(&buf, "42");
}
