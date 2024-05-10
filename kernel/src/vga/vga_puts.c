#include <vga.h>

void vga_puts(const char *s, t_vga_entry_color color, size_t i) {
	while (*s)
		VGA_MEMORY[i++] = vga_entry(*s++, color);
}
