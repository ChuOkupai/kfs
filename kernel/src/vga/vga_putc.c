#include <vga.h>

void vga_putc(char c, t_vga_entry_color color, size_t i) {
	VGA_MEMORY[i] = vga_entry(c, color);
}

