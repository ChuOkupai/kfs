#include <string.h>
#include <tty.h>

static void workspace_switch(size_t next) {
	t_workspace *w = tty_get_current_workspace();
	t_workspace *next_w = g_term->workspaces + next;

	// Save the current workspace
	memcpy(w->buf, VGA_MEMORY, VGA_BUFSIZE * sizeof(t_vga_entry));
	// Switch to the next workspace
	memcpy(VGA_MEMORY, next_w->buf, VGA_BUFSIZE * sizeof(t_vga_entry));
	g_term->current_workspace = next;
	tty_cursor_update();
}

void tty_prev_workspace() {
	workspace_switch((g_term->current_workspace + MAX_WORKSPACES - 1) % MAX_WORKSPACES);
}

void tty_next_workspace() {
	workspace_switch((g_term->current_workspace + 1) % MAX_WORKSPACES);
}
