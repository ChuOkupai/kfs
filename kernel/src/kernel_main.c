#include <boot.h>
#include <shell.h>

#if !defined(__i386__)
# error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main() {
	run_boot_seq();
	shell_run();
}
