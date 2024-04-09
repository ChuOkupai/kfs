#include <string.h>
#include <tty.h>

static void switch_screen(size_t next) {
	t_workspace *w = tty_current_workspace();
	memcpy(w->buffer, VGA_MEMORY, sizeof(w->buffer));
	g_tty->workspace_index = next;
	w = tty_current_workspace();
	memcpy(VGA_MEMORY, w->buffer, sizeof(w->buffer));
}

t_workspace *tty_current_workspace() {
	return g_tty->workspaces + g_tty->workspace_index;
}

void tty_prev_workspace() {
	switch_screen((g_tty->workspace_index + MAX_WORKSPACES - 1) % MAX_WORKSPACES);

}

void tty_next_workspace() {
	switch_screen((g_tty->workspace_index + 1) % MAX_WORKSPACES);
}
