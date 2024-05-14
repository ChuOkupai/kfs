#include <shortcut.h>
#include <timer.h>
#include <tty.h>

static inline void check_prompt(t_workspace *w, const char *prompt) {
	if (w->rl_start)
		return;
	tty_puts(prompt);
	w->rl_start = w->rl_cursor;
	tty_update();
}

static inline void get_user_input(t_workspace *w, const char *prompt) {
	t_key_sequence seq[KEY_SEQUENCE_MAX_LENGTH] = { 0 };
	t_key key;

	check_prompt(w, prompt);
	while (1) {
		wait_for_keypress(&key);
		if (key.state == KEY_RELEASED) {
			key_sequence_remove(seq, key.scancode);
			continue;
		}
		key_sequence_append(seq, key.scancode);
		if (shortcut_dispatch(seq)) {
			w = tty_current_workspace();
			check_prompt(w, prompt);
		} else {
			char c = scancode_to_ascii(key.scancode);
			if (c == '\n')
				break;
			if (c && c != '\t') {
				tty_putc(c);
			} else
				continue;
		}
		tty_update();
	}
}

static inline void extract_line(char *buf, t_workspace *w) {
	size_t i;
	for (i = w->rl_start; vga_getc(i); ++i)
		buf[i - w->rl_start] = vga_getc(i);
	buf[i - w->rl_start] = 0;
	w->rl_start = 0;
	tty_putc('\n');
	tty_update();
}

char *tty_readline(const char *prompt) {
	static char buf[TTY_BUFSIZE];

	get_user_input(tty_current_workspace(), prompt);
	extract_line(buf, tty_current_workspace());
	return buf;
}
