#include <macros.h>
#include <shortcut.h>
#include <tty.h>

static void move_cursor_left() {
	tty_move_cursor(-1);
}

static void move_cursor_right() {
	tty_move_cursor(1);
}

static void page_down() {
	tty_scroll_down(TTY_HEIGHT);
}

static void scroll_down() {
	tty_scroll_down(1);
}

const t_shortcut g_shortcuts[] = {
	{ { SCANCODE_LEFT_CTRL, SCANCODE_U }, tty_erase_line },
	{ { SCANCODE_LEFT_CTRL, SCANCODE_L }, tty_clear },
	{ { SCANCODE_LEFT_CTRL, SCANCODE_ARROW_LEFT }, tty_prev_workspace },
	{ { SCANCODE_LEFT_CTRL, SCANCODE_ARROW_RIGHT }, tty_next_workspace },
	{ { SCANCODE_ARROW_LEFT }, move_cursor_left },
	{ { SCANCODE_ARROW_RIGHT }, move_cursor_right },
	{ { SCANCODE_ARROW_DOWN }, scroll_down },
	{ { SCANCODE_PAGE_DOWN }, page_down }
};

bool shortcut_dispatch(t_key_sequence *seq) {
	for (size_t i = 0; i < SIZEOF_ARRAY(g_shortcuts); ++i)
		if (!key_sequence_compare(seq, g_shortcuts[i].seq)) {
			g_shortcuts[i].handler();
			return true;
		}
	return false;
}
