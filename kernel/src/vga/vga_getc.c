#include <vga.h>

t_vga_entry vga_getc(size_t x, size_t y) {
	return VGA_MEMORY[y * VGA_WIDTH + x];
}
