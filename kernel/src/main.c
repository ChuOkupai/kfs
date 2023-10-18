#include <stdint.h>
#include "utils.h"
#include "tty.h"

#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
# error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main()
{
	t_tty buf;
	tty_init(&buf);
	tty_setcolor(&buf, vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
	tty_puts(&buf, "42");
}
