#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <key_sequence.h>
#include <macros.h>
#include <timer.h>
#include <tty.h>

static inline char get_random_char() {
	char c;
	do {
		c = rand() % 127;
	}	while (!isprint(c));
	return c;
}

static inline t_vga_entry_color get_random_color() {
	return vga_entry_color(rand() % 16, rand() % 16);
}

static inline void squeeze_randomly(int k) {
	while (k--) {
		size_t offset = rand() % (VGA_WIDTH / 2) + 1;
		memmove(VGA_MEMORY + offset, VGA_MEMORY, (VGA_BUFSIZE - offset) * sizeof(t_vga_entry));
		for (size_t i = 0; i < offset; ++i)
			vga_putc(get_random_char(), tty_get_color(), i);
		timer_wait(rand() % 20);
	}
}

static inline void replace_randomly(int k) {
	while (k--) {
		char c = get_random_char();
		t_vga_entry_color color = get_random_color();
		size_t i = rand() % VGA_BUFSIZE;
		vga_putc(c, color, i);
		timer_wait(1);
	}
}

static inline void show_bsod() {
	const char *lines[] = {
		"                                    chor.iso", "",
		"    An error has occured. To continue:", "",
		"    Press CTRL+ALT+DEL to restart your computer. If you do this",
		"    you will lose any unsaved information in all open applications.", "",
		"    Error: 42 : DEAD : F0CACC1A", "",
		"                          Press any key to continue "
	};
	t_vga_entry_color color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
	tty_set_color(color);
	tty_clear();
	vga_clear(color);
	for (size_t i = 0; i < 8; ++i)
		tty_putc('\n');
	for (size_t i = 0; i < SIZEOF_ARRAY(lines); ++i)
		puts(lines[i]);
	tty_set_cursor_position(17 * TTY_WIDTH + 52);
	tty_set_cursor_type(CURSOR_TYPE_UNDERLINE);
	tty_update();
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		VGA_MEMORY[i] = vga_entry(vga_getc(i), color);
	for (size_t i = VGA_BUFSIZE - VGA_WIDTH; i < VGA_BUFSIZE; ++i)
		VGA_MEMORY[i] = vga_entry(0, color);
	color = vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_LIGHT_GREY);
	for (size_t i = 0; i < 10; ++i) {
		size_t j = i + 8 * VGA_WIDTH + 35;
		vga_putc(vga_getc(j), color, j);
	}
}

static inline void wait_before_reboot() {
	t_key_sequence seq[KEY_SEQUENCE_MAX_LENGTH] = { 0 },
	terminate[KEY_SEQUENCE_MAX_LENGTH] =
		{ SCANCODE_LEFT_CTRL, SCANCODE_LEFT_ALT, SCANCODE_DELETE };
	t_key key;
	while (1) {
		wait_for_keypress(&key);
		if (key.state == KEY_RELEASED) {
			key_sequence_remove(seq, key.scancode);
			continue;
		}
		key_sequence_append(seq, key.scancode);
		if (!key_sequence_compare(seq, terminate))
			break;
	}
	asm volatile("int $0x3");
}

void bsod() {
	tty_set_cursor_type(CURSOR_TYPE_NONE);
	squeeze_randomly(100);
	replace_randomly(200);
	timer_wait(2000);
	show_bsod();
	wait_before_reboot();
}
