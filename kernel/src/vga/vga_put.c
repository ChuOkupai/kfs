#include "vga.h"

void vga_put(char c, uint8_t color, size_t x, size_t y) {
	VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(c, color);
}
