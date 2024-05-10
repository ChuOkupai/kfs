#include <tty.h>

t_tty g_tty_storage;
t_tty *g_tty = &g_tty_storage;

static inline void workspace_init(t_workspace *w) {
	w->rl_start = 0;
	w->rl_cursor = 0;
	w->color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t i = 0; i < TTY_BUFSIZE; ++i)
		w->buffer[i] = vga_entry(0, w->color);
}

void tty_init() {
	g_tty->workspace_index = 0;
	for (size_t i = 0; i < MAX_WORKSPACES; ++i)
		workspace_init(g_tty->workspaces + i);
	vga_clear(tty_current_workspace()->color);
	tty_set_cursor_type(CURSOR_TYPE_NONE);
}
