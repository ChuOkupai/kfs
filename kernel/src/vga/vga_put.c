#include <vga.h>

void vga_put(char c, t_vga_entry_color color, size_t x, size_t y) {
	VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void vga_put_color(t_vga_entry_color color,  size_t x, size_t y) {
	VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(VGA_MEMORY[y * VGA_WIDTH + x] >> 8, color);
}
