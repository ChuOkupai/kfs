#include <vga.h>

void vga_fill(char c, t_vga_entry_color color, size_t i, size_t n) {
	for (size_t j = 0; j < n; ++j)
		VGA_MEMORY[i + j] = vga_entry(c, color);
}
