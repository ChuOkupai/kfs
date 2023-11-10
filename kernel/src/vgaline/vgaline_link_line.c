#include <vgaline.h>
#include <tty.h>

void	vgaline_link_line(t_list_vga_line *new_line, t_list_vga_line *start)
{
	t_list_vga_line *swap;
	if (new_line == start)
		return ;
	swap = start->next;
	new_line->prev = start;
	start->next = new_line;
	new_line->next = swap;
	if (new_line->next)
		new_line->next->prev = new_line;
}