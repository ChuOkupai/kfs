#include <string.h>
#include <bitset.h>
#include <tty.h>

t_tty g_term_storage;
t_tty *g_term = &g_term_storage;

static inline void workspace_init(t_workspace *s) {
	s->row = 0;
	s->column = 0;
	s->color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		s->buf[i] = vga_entry(' ', s->color);
}

static inline void run_boot_sequence() {
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

	vga_fill(' ', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		if (bitset_is_set(boot_mask, i))
			VGA_MEMORY[i] = vga_entry(' ', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

void tty_init() {
	g_term->current_workspace = 0;
	for (size_t i = 0; i < MAX_WORKSPACES; ++i)
		workspace_init(g_term->workspaces + i);
	run_boot_sequence();
}
