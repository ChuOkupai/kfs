#include <stdio.h>
#include <string.h>
#include <io.h>
#include <tty.h>

static inline void update_cursor(t_workspace *w) {
	if (g_tty->cursor_type != CURSOR_TYPE_NONE) {
		uint16_t pos = w->cursor_y * VGA_WIDTH + w->cursor_x;
		outb(0x3D4, 0x0F);
		outb(0x3D5, (uint8_t) (pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
	}
}

static inline void update_status_bar(t_workspace *w) {
	t_vga_entry_color color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_BLUE);
	vga_fill_line(0, color, VGA_HEIGHT - 1);
	vga_puts(" chor.iso", color, 0, VGA_HEIGHT - 1);

	char buf[32];
	sprintf(buf, " %hhu, %hhu | Workspace %d ", w->cursor_x, w->cursor_y,
		g_tty->workspace_index + 1);
	color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_CYAN);
	vga_puts(buf, color, VGA_WIDTH - strlen(buf), VGA_HEIGHT - 1);
}

void tty_update() {
	t_workspace *w = tty_current_workspace();
	update_cursor(w);
	update_status_bar(w);
}
