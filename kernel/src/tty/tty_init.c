#include <string.h>
#include <vgaline.h>
#include <tty.h>

t_tty *term_storage(void)
{
	static t_tty g_term_storage;
	return (&g_term_storage);
}

static inline void workspace_init(t_workspace *s) {
	memset(s, 0, sizeof(t_workspace));
	s->top_line = vgaline_alloc_safely();
	s->on_focus_line = s->top_line;
	s->starting_line = s->top_line;
	s->color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE);
}

void tty_init() {
	term_storage()->current_workspace = 0;
	for (size_t i = 0; i < MAX_WORKSPACES; ++i)
	{
		workspace_init(term_storage()->workspaces + i);
	}
}
