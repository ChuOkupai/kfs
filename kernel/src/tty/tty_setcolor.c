#include <tty.h>

void tty_setcolor(t_vga_entry_color color) {
	tty_get_current_workspace()->color = color;
}
