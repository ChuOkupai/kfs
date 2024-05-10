#include <stdio.h>
#include <string.h>
#include <boot.h>
#include <memory.h>
#include <tty.h>

#if !defined(__i386__)
# error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main() {
	run_boot_seq();
	while (1) {
		char *buf = tty_readline("> ");
		hexdump(buf, strlen(buf) + 1);
	}
}
