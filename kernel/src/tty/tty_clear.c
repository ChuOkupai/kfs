#include <tty.h>
#include <vgaline.h>

void tty_clear() {
	t_workspace *w = tty_get_current_workspace();
	t_list_vga_line* end = w->on_focus_line;

	while (end->next)
		end = end->next;
	while (end->prev)
	{
		end = end->prev;
		vgaline_free(end->next);
	}
	vgaline_clear(end);
	w->on_focus_line = end;
	w->top_line = end;
	w->row = 0;
	w->column = 0;
	tty_print_partial_screen(0, w->top_line);
	tty_cursor_update();
}
