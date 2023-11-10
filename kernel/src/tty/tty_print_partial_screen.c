#include <vga.h>
#include <vgaline.h>
#include <tty.h>

void	tty_print_partial_screen(size_t row, t_list_vga_line *starting)
{
	for (; starting && row < VGA_HEIGHT; starting = starting->next)
		vga_put_line(starting->buff, row++);
	while (row < VGA_HEIGHT)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
			vga_put('\0', tty_get_current_workspace()->color, x, row);
		row++;
	}
}