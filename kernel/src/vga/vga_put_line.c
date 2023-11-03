#include <vga.h>
#include <string.h>

void vga_put_line(t_vga_entry entry[VGA_WIDTH], size_t x)
{
	memcpy(VGA_MEMORY + x * VGA_WIDTH, entry, VGA_WIDTH * sizeof(t_vga_entry));
}