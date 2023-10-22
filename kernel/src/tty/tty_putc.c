#include <tty.h>

static inline void workspace_putc(t_workspace *s, char c) {
	if (c == '\n') {
		s->column = 0;
		if (++s->row == VGA_HEIGHT)
			s->row = 0;
		return;
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
