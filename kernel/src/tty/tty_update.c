#include <stdio.h>
#include <string.h>
#include <io.h>
#include <tty.h>

static inline void update_cursor(t_workspace *w) {
	if (g_tty->cursor_type != CURSOR_TYPE_NONE) {
		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t) (w->rl_cursor & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t) ((w->rl_cursor >> 8) & 0xFF));
	}
}

static inline void update_status_bar(t_workspace *w) {
	char buf[64];
	size_t x = w->rl_cursor % TTY_WIDTH, y = w->rl_cursor / TTY_WIDTH;
	t_vga_entry_color color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_BLUE);
	vga_fill(0, color, TTY_BUFSIZE, VGA_WIDTH);
	vga_puts(" chor.iso", color, TTY_BUFSIZE);
	sprintf(buf, " %zu, %zu | Workspace %d ", x, y, g_tty->workspace_index + 1);
	color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_CYAN);
	vga_puts(buf, color, VGA_BUFSIZE - strlen(buf));
}

void tty_update() {
	t_workspace *w = tty_current_workspace();
	update_cursor(w);
	update_status_bar(w);
}
