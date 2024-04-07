#include <macros.h>
#include <shortcut.h>
#include <tty.h>

static void scroll_down() {
	tty_scroll_down(1);
}

static void page_down() {
	tty_scroll_down(TTY_HEIGHT);
}

const t_shortcut g_shortcuts[] = {
	{
		.seq = { SCANCODE_LEFT_CTRL, SCANCODE_U },
		.handler = tty_erase_line
	}, {
		.seq = { SCANCODE_LEFT_CTRL, SCANCODE_L },
		.handler = tty_clear
	}, {
		.seq = { SCANCODE_LEFT_CTRL, SCANCODE_ARROW_LEFT },
		.handler = tty_prev_workspace
	}, {
		.seq = { SCANCODE_LEFT_CTRL, SCANCODE_ARROW_RIGHT },
		.handler = tty_next_workspace
	}, {
		.seq = { SCANCODE_ARROW_DOWN },
		.handler = scroll_down
	}, {
		.seq = { SCANCODE_PAGE_DOWN },
		.handler = page_down
	}
};

bool shortcut_dispatch(t_key_sequence *seq) {
	for (size_t i = 0; i < SIZEOF_ARRAY(g_shortcuts); ++i)
		if (!key_sequence_compare(seq, g_shortcuts[i].seq)) {
			g_shortcuts[i].handler();
			return true;
		}
	return false;
}
