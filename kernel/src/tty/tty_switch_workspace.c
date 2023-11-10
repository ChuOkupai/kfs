#include <string.h>
#include <vgaline.h>
#include <tty.h>

static void workspace_switch(size_t next) {
	term_storage()->current_workspace = next;
	tty_print_partial_screen(0, tty_get_current_workspace()->top_line);
	tty_cursor_update();
}

void tty_prev_workspace() {
	workspace_switch((term_storage()->current_workspace + MAX_WORKSPACES - 1) % MAX_WORKSPACES);
}

void tty_next_workspace() {
	workspace_switch((term_storage()->current_workspace + 1) % MAX_WORKSPACES);
}
