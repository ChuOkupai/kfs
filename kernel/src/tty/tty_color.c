#include <tty.h>

void tty_set_color(t_vga_entry_color color) {
	t_workspace *w = tty_current_workspace();
	w->color = color;
}
