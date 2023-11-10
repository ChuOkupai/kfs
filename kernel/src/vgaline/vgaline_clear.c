#include <vgaline.h>
#include <tty.h>

static inline void	fill_vga_line(t_list_vga_line *to_be_filled, t_vga_entry entry)
{
	for (size_t k = 0; k < VGA_WIDTH; k++)
		to_be_filled->buff[k] = entry;
}

void	vgaline_clear(t_list_vga_line *to_be_filled)
{
	t_workspace				*w = tty_get_current_workspace();
	t_vga_entry				blank = vga_entry('\0', w->color);

	fill_vga_line(to_be_filled, blank);
}