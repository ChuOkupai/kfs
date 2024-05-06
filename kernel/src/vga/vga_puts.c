#include <vga.h>

void vga_puts(const char *s, t_vga_entry_color color, size_t i) {
	while (*s)
		vga_putc(*s++, color, i++);
}
