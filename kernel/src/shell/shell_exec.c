#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <macros.h>
#include <shell.h>
#include <stack.h>
#include <tty.h>

static const char *g_colors[] = {
	"blue", "green", "cyan", "red", "magenta", "brown", "light_gray", "dark_gray",
	"light_blue", "light_green", "light_cyan", "light_red", "light_magenta",
	"light_brown", "white"
};

static void halt_handler() {
	asm volatile("cli; hlt");
}

static void help_handler() {
	const char *help[][2] = {
		{ "clear", "Clears the terminal" },
		{ "halt", "Halts the system" },
		{ "help", "Displays this help message" },
		{ "print_stack_info", "Prints the stack information" },
		{ "reboot", "Reboots the system" },
		{ "set_term_color", "Sets the terminal color" }
	};
	puts("Available commands:");
	for (size_t i = 0; i < SIZEOF_ARRAY(help); ++i) {
		printf("%-20s", help[i][0]);
		t_vga_entry_color old_color = tty_get_color();
		tty_set_color(vga_entry_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK));
		puts(help[i][1]);
		tty_set_color(old_color);
	}
}

static void reboot_handler() {
	asm volatile("int $0x3");
}

static void set_term_color_handler(char **args) {
	if (!args[1]) {
		shell_perror("usage: set_term_color <color>");
		return;
	} else if (!strcmp(args[1], "help")) {
		puts("List of available colors:");
		for (size_t i = 0; i < SIZEOF_ARRAY(g_colors); ++i)
			printf("%s\n", g_colors[i]);
		return;
	}
	for (char *p = (char *) args[1]; *p; ++p)
		*p = tolower(*p);
	size_t i = 0;
	for (; i < SIZEOF_ARRAY(g_colors); ++i) {
		if (!strcmp(args[1], g_colors[i]))
			break;
	}
	if (i == SIZEOF_ARRAY(g_colors)) {
		shell_perror("Invalid color");
		return;
	}
	tty_set_color(vga_entry_color(i + 1, tty_get_color() >> 4));
	t_cursor_type cursor_type = g_tty->cursor_type;
	tty_set_cursor_type(CURSOR_TYPE_NONE);
	tty_set_cursor_type(cursor_type);
}

const t_builtin g_builtins[] = {
	{ "clear", tty_clear },
	{ "halt", halt_handler },
	{ "help", help_handler },
	{ "print_stack_info", print_stack_info },
	{ "reboot", reboot_handler },
	{ "set_term_color", set_term_color_handler }
};

static int cmp(const void *a, const void *b) {
	const char *name = a;
	const t_builtin *builtin = b;
	return strcmp(name, builtin->name);
}

int shell_exec(char **args) {
	t_builtin *builtin = bsearch(*args, g_builtins, SIZEOF_ARRAY(g_builtins), sizeof(t_builtin), cmp);
	if (!builtin)
		return -1;
	builtin->handler(args);
	return 0;
}
