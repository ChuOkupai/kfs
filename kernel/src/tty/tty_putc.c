#include <vga.h>
#include <vgaline.h>
#include <tty.h>

static inline void workspace_putc(t_workspace *s, char c) {
	static t_list_vga_line	*start = NULL;
	static t_vga_entry				*on_focus = NULL;

	if (!start)
	{
		start = alloc_next_line();
		on_focus = start->line;
	}
	if (c == '\n' || start->line )
}

void tty_putc(char c) {
	workspace_putc(tty_get_current_workspace(), c);
}
