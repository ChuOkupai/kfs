#include <string.h>
#include <tty.h>

void tty_set_last_command(const char *command) {
	t_workspace *w = tty_current_workspace();
	size_t n = strlen(command);
	if (n >= TTY_BUFSIZE)
		n = TTY_BUFSIZE - 1;
	memcpy(w->last_command, command, n);
	w->last_command[n] = 0;
}

void tty_show_last_command() {
	t_workspace *w = tty_current_workspace();
	if (w->rl_start == w->rl_cursor)
		tty_puts(w->last_command);
}
