#include <stdio.h>
#include <bonus.h>
#include <boot.h>
#include <shortcut.h>
#include <tty.h>

#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
# error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

static void loop() {
	t_key_sequence seq[KEY_SEQUENCE_MAX_LENGTH] = { 0 };
	t_key key;
	while (1) {
		wait_for_keypress(&key);
		if (key.state == KEY_PRESSED) {
			key_sequence_append(seq, key.scancode);
			if (!shortcut_dispatch(seq)) {
				char c = scancode_to_ascii(key.scancode);
				if (c && c != '\t' && c != 0x7F) {
					tty_putc(c);
					tty_update();
				} else
					continue;
			}
			tty_update();
		} else if (key.state == KEY_RELEASED)
			key_sequence_remove(seq, key.scancode);
	}
}

void kernel_main() {
	boot();
	if (BONUS)
		loop();
	else {
		printf("%d\n", 42);
		tty_update();
		while (1);
	}
}
