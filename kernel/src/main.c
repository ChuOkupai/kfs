#include <stdint.h>
#include <string.h>
#include <keyboard.h>
#include <tty.h>

#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
# error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main()
{
	tty_init();
	init_keyboard();
	tty_puts("42\n");
	while (1)
		handle_keyboard_input();
}