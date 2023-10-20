#include "vga.h"

void vga_fill(char c, t_vga_entry_color color) {
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i)
		VGA_MEMORY[i] = vga_entry(c, color);
}
