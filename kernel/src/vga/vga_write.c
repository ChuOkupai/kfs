#include <string.h>
#include <vga.h>

void vga_write(const t_vga_entry *entry, size_t y) {
	memcpy(VGA_MEMORY + y * VGA_WIDTH, entry, VGA_WIDTH * sizeof(t_vga_entry));
}
