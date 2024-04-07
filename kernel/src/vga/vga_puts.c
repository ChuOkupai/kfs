#include <vga.h>

void vga_puts(const char *s, t_vga_entry_color color, size_t x, size_t y) {
	size_t i = 0;
	while (s[i] && x + i < VGA_WIDTH) {
		vga_putc(s[i], color, x + i, y);
		++i;
	}
}
