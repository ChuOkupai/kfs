#include <io.h>
#include <tty.h>

void tty_move_cursor(int8_t direction) {
	t_workspace *w = tty_current_workspace();
	if (direction < 0) {
		if (w->cursor_x > 0)
			--w->cursor_x;
		else if (w->cursor_y > 0 && (vga_getc(TTY_WIDTH - 1, w->cursor_y - 1) & 0xFF)) {
			w->cursor_x = TTY_WIDTH - 1;
			--w->cursor_y;
		}
	} else if ((vga_getc(w->cursor_x, w->cursor_y) & 0xFF)) {
		if (w->cursor_x < TTY_WIDTH - 1)
			++w->cursor_x;
		else if (w->cursor_y < TTY_HEIGHT - 1) {
			w->cursor_x = 0;
			++w->cursor_y;
		}
	}
}

void tty_set_cursor_pos_from_index(size_t index) {
	t_workspace *w = tty_current_workspace();
	w->cursor_x = index % TTY_WIDTH;
	w->cursor_y = index / TTY_WIDTH;
}

void tty_set_cursor_pos(uint8_t x, uint8_t y) {
	t_workspace *w = tty_current_workspace();
	w->cursor_x = x;
	w->cursor_y = y;
}

void tty_set_cursor_type(t_cursor_type type) {
	g_tty->cursor_type = type;
	outb(0x3D4, 0x0A);
	if (type == CURSOR_TYPE_NONE)
		outb(0x3D5, 0x20);
	else {
		outb(0x3D5, (inb(0x3D5) & 0xC0) | type);
		outb(0x3D4, 0x0B);
		outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
	}
}
