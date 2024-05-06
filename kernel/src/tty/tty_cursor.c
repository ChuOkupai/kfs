#include <io.h>
#include <tty.h>

void tty_move_cursor(int8_t direction) {
	t_workspace *w = tty_current_workspace();
	size_t i = w->cursor_index;
	if (direction < 0) {
		if (i && ((i % TTY_WIDTH) || vga_getc(i - 1))) {
			do
				--i;
			while (i && !vga_getc(i));
		}
	} else if (vga_getc(i) && i < TTY_BUFSIZE - 1)
		++i;
	w->cursor_index = i;
}

void tty_move_end_of_line() {
	t_workspace *w = tty_current_workspace();
	size_t i = w->cursor_index;
	while (i < TTY_BUFSIZE && (VGA_MEMORY[i] & 0xFF))
		++i;
	if (i == TTY_BUFSIZE) {
		i -= TTY_WIDTH;
		tty_scroll_up(1);
	}
	w->cursor_index = i;
}

void tty_move_start_of_line() {
	t_workspace *w = tty_current_workspace();
	size_t i = w->cursor_index;
	while (i > 0 && vga_getc(i - 1))
		--i;
	w->cursor_index = i;
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
