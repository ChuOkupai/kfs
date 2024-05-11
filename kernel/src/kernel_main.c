#include <stdio.h>
#include <boot.h>
#include <memory.h>
#include <shell.h>
#include <tty.h>

#if !defined(__i386__)
# error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main() {
	run_boot_seq();
	while (1) {
		char *buf = tty_readline("> ");
		char *args[MAX_ARGS];
		if (parse_command(args, buf) < 0) {
			print_error("Too many arguments");
			continue;
		}
		if (!*args[0])
			continue;
		if (builtin_exec(args) < 0)
			print_error("Command not found");
	}
}
