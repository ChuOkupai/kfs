#include <vga.h>
#include <vga.h>

void vga_put_rect(char c, t_vga_entry_color color, size_t x, size_t y, size_t width, size_t height) {
	for (height += y; y < height; ++y)
		for (size_t i = 0; i < width; ++i)
			vga_put(c, color, x + i, y);
}
