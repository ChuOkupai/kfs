#include <vga.h>

char vga_getc(size_t i) {
	return VGA_MEMORY[i] & 0xFF;
}
