#include <string.h>
#include <macros.h>
#include <tty.h>

void tty_scroll_up() {
	t_workspace *w = tty_current_workspace();
	if (w->rl_start && w->rl_start < TTY_WIDTH)
		return;
	memmove(VGA_MEMORY, VGA_MEMORY + TTY_WIDTH, (TTY_BUFSIZE - TTY_WIDTH) * sizeof(t_vga_entry));
	vga_fill(0, TTY_DEFAULT_COLOR, TTY_BUFSIZE - TTY_WIDTH, TTY_WIDTH);
	w->rl_cursor -= TTY_WIDTH;
	if (w->rl_start)
		w->rl_start -= TTY_WIDTH;
}
