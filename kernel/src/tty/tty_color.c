#include <tty.h>

t_vga_entry_color tty_get_color() {
	t_workspace *w = tty_current_workspace();
	return w->color;
}

void tty_set_color(t_vga_entry_color color) {
	t_workspace *w = tty_current_workspace();
	w->color = color;
}
