#include <vga.h>

inline uint16_t vga_entry_cmp(t_vga_entry c1, t_vga_entry c2)
{
	return (c1 - c2);
}