#include <tty.h>

static inline void workspace_putc(t_workspace *s, char c) {
	t_vga_color focus_color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
	if (c == '\a')
	{
		vga_put_color(s->color, s->column, s->row);
		t_vga_entry	blank = vga_entry('\0', s->color);
		if (s->column != 0)
			--s->column;
		else if (s->row != 0)
		{
			--s->row;
			s->column = VGA_WIDTH;
			while (s->column != 0
			&& (!vga_entry_cmp(VGA_MEMORY[s->row * VGA_WIDTH + s->column], blank)
			|| !vga_entry_cmp(VGA_MEMORY[s->row * VGA_WIDTH + s->column], '\0' | focus_color << 8)))
				s->column--;
		}
		vga_put('\0', focus_color, s->column, s->row);
		return ;
	}

	vga_put(c, s->color, s->column, s->row);
	if (c == '\n') {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
		return;
	}
	if (++s->column == VGA_WIDTH) {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
	}
	vga_put_color(focus_color, s->column, s->row);
}

void tty_putc(char c) {
	workspace_putc(tty_get_current_workspace(), c);
}
