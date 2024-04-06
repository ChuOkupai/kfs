#include <tty.h>

static void switch_screen(size_t next) {
	g_tty->workspace_index = next;
	tty_update();
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
