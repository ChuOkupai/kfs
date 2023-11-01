#include <vga.h>
#include <vgaline.h>
#include <tty.h>

static inline void workspace_putc(t_workspace *s, char c) {
	static struct s_list_vga_line	*start = alloc_next_line();
	static t_vga_entry				*on_focus = start->line + 0;
	t_vga_entry_color				focus_color = VGA_COLOR_BLACK | VGA_COLOR_WHITE << 4;

	*on_focus |= focus_color << 8;
}

void tty_putc(char c) {
	workspace_putc(tty_get_current_workspace(), c);
}
