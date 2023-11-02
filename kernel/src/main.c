#include <bitset.h>
#include <keyboard.h>
#include <timer.h>
#include <tty.h>
#include <stdio.h>

#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
# error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

static inline void run_frame(const t_vga_color c) {
	// 42 in pixel art
	const t_bitset boot_mask[BITSET_SIZE(VGA_BUFSIZE)] = {
		0, 0, 0, 0x87ff8000, 0xfffff, 0xc0000000, 0xfcff81ff, 0xf,
		0x807ff000, 0xffc3f, 0xfc000000, 0xfc0f803f, 0xf, 0x800ffe00, 0xffc03, 0xff800000,
		0xfc008003, 0xf, 0xffe0, 0xffe00, 0x7ff80000, 0xff000000, 0x3, 0x1ffc,
		0xffc0, 0x7ff0000, 0x3ff00000, 0xc0000000, 0x1ff, 0x1ffc, 0x7fe000, 0x7ff0000,
		0xf0000000, 0x87ffffff, 0x803ff, 0xfffff000, 0x3ff87ff, 0xf000000c, 0x87ffffff, 0xf03ff,
		0xfffff000, 0xc3ff87ff, 0xf000000f, 0x87ffffff, 0xff3ff, 0, 0xffff87ff, 0xf,
		0x7ff0000, 0, 0, 0x7ff, 0, 0x7ff0000, 0, 0,
		0x7ff, 0, 0x7ff0000, 0, 0, 0, 0
	};
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		if (bitset_is_set(boot_mask, i))
			VGA_MEMORY[i] = vga_entry(' ', vga_entry_color(VGA_COLOR_BLACK, c));
}

static inline void run_boot_sequence() {
	const t_vga_color colors_sequence[] = {
		VGA_COLOR_RED,
		VGA_COLOR_GREEN,
		VGA_COLOR_BLUE,
		VGA_COLOR_BLACK
	};
	tty_setcolor(vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
	tty_clear();
	for (size_t i = 0; i < SIZEOF_ARRAY(colors_sequence); ++i) {
		run_frame(colors_sequence[i]);
		timer_wait(200);
	}
	timer_wait(1000);
	tty_setcolor(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	tty_clear();
}

void kernel_main()
{
	timer_init();
	tty_init();
	run_boot_sequence();
	tty_cursor_enable(CURSOR_TYPE_UNDERLINE);
	init_keyboard();
	tty_clear();
	printf("%d\n", 42);
	while (1)
		handle_keyboard_input();
}
