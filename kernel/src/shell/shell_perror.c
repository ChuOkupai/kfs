#include <stdio.h>
#include <tty.h>

void shell_perror(const char *desc) {
	t_vga_entry_color old_color = tty_get_color();
	tty_set_color(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
	printf("error: %s\n", desc);
	tty_set_color(old_color);
}
