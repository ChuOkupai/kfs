#include <vga.h>

void vga_fill_line(char c, t_vga_entry_color color, size_t y) {
	for (size_t x = 0; x < VGA_WIDTH; ++x)
		VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void vga_fill(char c, t_vga_entry_color color) {
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i)
		VGA_MEMORY[i] = vga_entry(c, color);
}
