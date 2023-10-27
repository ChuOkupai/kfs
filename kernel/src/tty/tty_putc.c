#include <tty.h>
#include <stdio.h>

void	print_hexa(uint16_t num, char* s)
{
	char	hex[] = "0123456789abcdef";
	printf("\n\n\n\n%s => %c%c%c%c\n", s, hex[num >> 12], hex[num >> 8 & 0xf], hex[num >> 4 & 0xf], hex[num & 0xf]);
}

static inline void workspace_putc(t_workspace *s, char c) {

	if (c == '\n') {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
		return;
	}
	else if (c == '\a')
	{
		t_vga_entry	blank = vga_entry('\0', s->color);
		if (s->column != 0)
			--s->column;
		else
		{
			if (s->row == 0)
				return ;
			--s->row;
			s->column = VGA_WIDTH;
			while (s->column != 0 && !vga_entry_cmp(VGA_MEMORY[s->row * VGA_WIDTH + s->column], blank))
			{
				s->column--;
			}
		}
		vga_put('\0', s->color, s->column, s->row);
		return ;
	}
	vga_put(c, s->color, s->column, s->row);
	if (++s->column == VGA_WIDTH) {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
	}
}

void tty_putc(char c) {
	workspace_putc(tty_get_current_workspace(), c);
}
