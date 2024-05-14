#include <stdlib.h>
#include <macros.h>
#include <shortcut.h>
#include <tty.h>

static void move_cursor_left() {
	tty_move_cursor(-1);
}

static void move_cursor_right() {
	tty_move_cursor(1);
}

static void switch_cursor_style() {
	tty_set_cursor_type(g_tty->cursor_type ^ CURSOR_TYPE_UNDERLINE);
}

const t_shortcut g_shortcuts[] = {
	{ { SCANCODE_LEFT_CTRL, SCANCODE_Q }, switch_cursor_style },
	{ { SCANCODE_LEFT_CTRL, SCANCODE_U }, tty_erase_line },
	{ { SCANCODE_LEFT_CTRL, SCANCODE_L }, tty_clear },
	{ { SCANCODE_LEFT_CTRL, SCANCODE_ARROW_LEFT }, tty_prev_workspace },
	{ { SCANCODE_LEFT_CTRL, SCANCODE_ARROW_RIGHT }, tty_next_workspace },
	{ { SCANCODE_RIGHT_CTRL, SCANCODE_Q }, switch_cursor_style },
	{ { SCANCODE_RIGHT_CTRL, SCANCODE_U }, tty_erase_line },
	{ { SCANCODE_RIGHT_CTRL, SCANCODE_L }, tty_clear },
	{ { SCANCODE_RIGHT_CTRL, SCANCODE_ARROW_LEFT }, tty_prev_workspace },
	{ { SCANCODE_RIGHT_CTRL, SCANCODE_ARROW_RIGHT }, tty_next_workspace },
	{ { SCANCODE_HOME }, tty_move_start_of_line },
	{ { SCANCODE_ARROW_UP }, tty_show_last_command },
	{ { SCANCODE_ARROW_LEFT }, move_cursor_left },
	{ { SCANCODE_ARROW_RIGHT }, move_cursor_right },
	{ { SCANCODE_END }, tty_move_end_of_line },
	{ { SCANCODE_ARROW_DOWN }, tty_scroll_up }
};

static int cmp(const void *a, const void *b) {
	const t_key_sequence *seq1 = a;
	const t_shortcut *s2 = b;
	return key_sequence_compare(seq1, s2->seq);
}

bool shortcut_dispatch(t_key_sequence *seq) {
	t_shortcut *shortcut = bsearch(seq, g_shortcuts, SIZEOF_ARRAY(g_shortcuts),
		sizeof(t_shortcut), cmp);
	if (!shortcut)
		return false;
	shortcut->handler();
	return true;
}
