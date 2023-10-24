#include <string.h>
#include <tty.h>

t_tty g_term_storage;
t_tty *g_term = &g_term_storage;

static inline void workspace_init(t_workspace *s) {
	s->row = 0;
	s->column = 0;
	s->color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		s->buf[i] = vga_entry(' ', s->color);
}

void tty_init() {
	g_term->current_workspace = 0;
	for (size_t i = 0; i < MAX_WORKSPACES; ++i)
		workspace_init(g_term->workspaces + i);
}
