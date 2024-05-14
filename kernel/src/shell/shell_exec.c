#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <macros.h>
#include <memory.h>
#include <shell.h>
#include <stack.h>
#include <timer.h>
#include <tty.h>

int g_remaining_calls_to_bsod = 0;

static const char *g_colors[] = {
	"blue", "green", "cyan", "red", "magenta", "brown", "light_gray", "dark_gray",
	"light_blue", "light_green", "light_cyan", "light_red", "light_magenta",
	"yellow", "white"
};

static void dump_stack_handler(char **args) {
	if (!args[1] || !args[2]) {
		shell_perror("usage: dump_stack <offset> <size>");
		return;
	}
	char *endptr;
	unsigned long offset = strtoul(args[1], &endptr, 0);
	if (*endptr || offset >= stack_size()) {
		shell_perror("Invalid offset");
		return;
	}
	unsigned long size = strtoul(args[2], &endptr, 0);
	if (*endptr || size > stack_size() - offset)
		shell_perror("Invalid size");
	else
		hexdump((void*)(&stack_bottom) + offset, size);
}

static void halt_handler() {
	asm volatile("cli; hlt");
}

static void help_handler() {
	const char *help[][2] = {
		{ "clear", "Clears the terminal" },
		{ "dump_stack", "Dumps the stack in both hexadecimal and ASCII" },
		{ "halt", "Halts the system" },
		{ "help", "Displays this help message" },
		{ "print_stack_info", "Prints the stack information" },
		{ "print_stack_trace", "Prints the stack trace" },
		{ "reboot", "Reboots the system" },
		{ "set_term_color", "Sets the terminal color" }
	};
	puts("Available commands:");
	for (size_t i = 0; i < SIZEOF_ARRAY(help); ++i) {
		printf("  %-20s", help[i][0]);
		t_vga_entry_color old_color = tty_get_color();
		tty_set_color(vga_entry_color(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK));
		puts(help[i][1]);
		tty_set_color(old_color);
	}
}

/**
 * LS is an easter egg.
 * It will trigger a BSOD after a random number of command inputs.
*/
static void ls_handler() {
	shell_perror(
		"The filesystem is not implemented. Please try again later.\n"
		"If the problem persists, please contact your system administrator.\n"
		"Error code: 0x00000042"
	);
	srand(4201 * pit_read());
	g_remaining_calls_to_bsod = rand() % 10 + 1;
}

static void reboot_handler() {
	asm volatile("int $0x3");
}

static void set_term_color_handler(char **args) {
	if (!args[1]) {
		shell_perror("usage: set_term_color (<color>|help)");
		return;
	} else if (!strcmp(args[1], "help")) {
		puts("List of available colors:");
		t_vga_entry_color old_color = tty_get_color();
		for (size_t i = 0; i < SIZEOF_ARRAY(g_colors); ++i) {
			tty_set_color(vga_entry_color(i + 1, tty_get_color() >> 4));
			printf("  %s\n", g_colors[i]);
		}
		tty_set_color(old_color);
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
	{ "dump_stack", dump_stack_handler },
	{ "halt", halt_handler },
	{ "help", help_handler },
	{ "ls", ls_handler },
	{ "print_stack_info", print_stack_info },
	{ "print_stack_trace", print_stack_trace },
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
