#include <tty.h>

void tty_cursor_update() {
	const t_workspace *w = tty_get_current_workspace();
	tty_cursor_set(w->column, w->row);
}
