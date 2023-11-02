#include <vga.h>
#include <vgaline.h>
#include <tty.h>

void	line_list_init(void)
{
	static t_list_vga_line	*start = alloc_next_line();
	static t_vga_entry				*on_focus = start->line + 0;
	t_vga_entry_color				focus_color = VGA_COLOR_BLACK | VGA_COLOR_WHITE << 4;

	*on_focus |= focus_color << 8;
	
}