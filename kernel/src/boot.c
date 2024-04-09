#include <string.h>
#include <bitset.h>
#include <keyboard.h>
#include <timer.h>
#include <tty.h>

/** 42 in pixel art. */
static const t_bitset g_boot_mask[BITSET_SIZE(VGA_BUFSIZE)] = {
	0, 0, 0, 0x87ff8000, 0xfffff, 0xc0000000, 0xfcff81ff, 0xf,
	0x807ff000, 0xffc3f, 0xfc000000, 0xfc0f803f, 0xf, 0x800ffe00, 0xffc03, 0xff800000,
	0xfc008003, 0xf, 0xffe0, 0xffe00, 0x7ff80000, 0xff000000, 0x3, 0x1ffc,
	0xffc0, 0x7ff0000, 0x3ff00000, 0xc0000000, 0x1ff, 0x1ffc, 0x7fe000, 0x7ff0000,
	0xf0000000, 0x87ffffff, 0x803ff, 0xfffff000, 0x3ff87ff, 0xf000000c, 0x87ffffff, 0xf03ff,
	0xfffff000, 0xc3ff87ff, 0xf000000f, 0x87ffffff, 0xff3ff, 0, 0xffff87ff, 0xf,
	0x7ff0000, 0, 0, 0x7ff, 0, 0x7ff0000, 0, 0,
	0x7ff, 0, 0x7ff0000, 0, 0, 0, 0
};

static inline void run_frame(const t_vga_color c) {
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		if (bitset_is_set(g_boot_mask, i))
			VGA_MEMORY[i] = vga_entry(' ', vga_entry_color(VGA_COLOR_BLACK, c));
}

static inline void run_boot_sequence() {
	const t_vga_color colors_sequence[] = {
		VGA_COLOR_RED,
		VGA_COLOR_GREEN,
		VGA_COLOR_BLUE,
		VGA_COLOR_BLACK
	};
	vga_fill(0, vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
	for (size_t i = 0; i < SIZEOF_ARRAY(colors_sequence); ++i) {
		run_frame(colors_sequence[i]);
		timer_wait(200);
	}
	timer_wait(1000);
}

void boot() {
	timer_init();
	tty_init();
	//run_boot_sequence();
	tty_set_cursor_type(CURSOR_TYPE_UNDERLINE);
	init_keyboard();
	tty_clear();
}
