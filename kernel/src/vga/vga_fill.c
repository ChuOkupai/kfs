#include <vga.h>

void vga_fill_n(char c, t_vga_entry_color color, size_t i, size_t n) {
	for (size_t j = 0; j < n; ++j)
		VGA_MEMORY[i + j] = vga_entry(c, color);
}

void vga_fill(char c, t_vga_entry_color color) {
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		VGA_MEMORY[i] = vga_entry(c, color);
}
