#include "vga.h"

void vga_fill(char c, uint8_t color) {
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i)
		VGA_MEMORY[i] = vga_entry(c, color);
}
