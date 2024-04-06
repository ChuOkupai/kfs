#include <string.h>
#include <vgaline.h>
#include <tty.h>

t_tty g_tty_storage;
t_tty *g_tty = &g_tty_storage;

static inline void workspace_init(t_workspace *w) {
	w->cursor_x = 0;
	w->cursor_y = 0;
	w->color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void tty_init() {
	g_tty->workspace_index = 0;
	for (size_t i = 0; i < MAX_WORKSPACES; ++i)
		workspace_init(g_tty->workspaces + i);
	tty_set_cursor_type(CURSOR_TYPE_NONE);
	tty_clear();
}
