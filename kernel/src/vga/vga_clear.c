#include <vga.h>

void vga_clear(t_vga_entry_color color) {
	vga_fill(0, color, 0, VGA_BUFSIZE);
}
