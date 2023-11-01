#pragma once
#include <stdbool.h>
#include <vga.h>

#define MAX_WORKSPACES 3

typedef enum e_cursor_type {
	CURSOR_TYPE_BLOCK,
	CURSOR_TYPE_UNDERLINE
}	t_cursor_type;

typedef struct s_workspace {
	t_vga_entry buf[VGA_BUFSIZE];
	size_t row;
	size_t column;
	t_vga_entry_color color;
}	t_workspace;

typedef struct s_tty {
	t_workspace workspaces[MAX_WORKSPACES];
	size_t current_workspace;
	bool cursor_enabled;
}	t_tty;

/** The global tty used by the kernel. */
extern t_tty *g_term;

/**
 * Gets the current workspace.
 * @return The current workspace.
 */
inline t_workspace *tty_get_current_workspace() {
	return g_term->workspaces + g_term->current_workspace;
}

/**
 * Clears the tty, resetting the cursor position to the top left.
 */
void tty_clear();

/**
 * Disables the cursor.
 */
void tty_cursor_disable();

/**
 * Enables the cursor.
 * @param type The type of cursor to use.
*/
void tty_cursor_enable(t_cursor_type type);

/**
 * Sets the cursor position.
 * @param x The new horizontal position of the cursor.
 * @param y The new vertical position of the cursor.
 */
void tty_cursor_set(size_t x, size_t y);

/**
 * Updates the cursor position to the current workspace's cursor position.
 */
void tty_cursor_update();

/**
 * Initializes the tty.
 */
void tty_init();

/**
 * Switches to the next workspace.
 */
void tty_next_workspace();

/**
 * Switches to the previous workspace.
 */
void tty_prev_workspace();

/**
 * Puts a character on the tty.
 * @param c The character to put on the tty.
 */
void tty_putc(char c);

/**
 * Puts a string on the tty.
 * @param s The string to put on the tty.
 */
void tty_puts(const char *s);

/**
 * Sets the color of the tty.
 * @param color The color to set the tty to.
 */
void tty_setcolor(t_vga_entry_color color);

/**
 * Writes data to the tty.
 * @param data The data to write to the tty.
 * @param size The size of the data to write to the tty.
 */
void tty_write(const char *data, size_t size);
