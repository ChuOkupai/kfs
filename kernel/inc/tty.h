#pragma once
#include <vga.h>

#define MAX_WORKSPACES	3
#define TTY_WIDTH		VGA_WIDTH
#define TTY_HEIGHT		(VGA_HEIGHT - 1)
#define TTY_BUFSIZE		(TTY_WIDTH * TTY_HEIGHT)

typedef enum e_cursor_type {
	CURSOR_TYPE_NONE,
	CURSOR_TYPE_BLOCK,
	CURSOR_TYPE_UNDERLINE
}	t_cursor_type;

typedef struct s_workspace {
	uint16_t			buffer[TTY_BUFSIZE];
	uint8_t				cursor_x;
	uint8_t				cursor_y;
	t_vga_entry_color	color;
}	t_workspace;

typedef struct s_tty {
	t_workspace		workspaces[MAX_WORKSPACES];
	size_t			workspace_index;
	t_cursor_type	cursor_type;
}	t_tty;

/** The global tty used by the kernel. */
extern t_tty *g_tty;

/**
 * Clears the tty, resetting the cursor position to the top left.
 */
void tty_clear();

/**
 * Gets the current workspace.
 * @return The current workspace.
*/
t_workspace *tty_current_workspace();

/**
 * Erases the current line.
*/
void tty_erase_line();

/**
 * Initializes the tty.
 */
void tty_init();

/**
 * Moves the cursor by a given offset.
 * If the direction is negative, the cursor will move to the left.
 * If the direction is positive, the cursor will move to the right.
 * @param direction The direction to move the cursor.
 */
void tty_move_cursor(int8_t direction);

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
 * Scrolls the tty up by a given number of lines.
 * The lines are discarded.
 * @param lines The number of lines to scroll up.
 */
void tty_scroll_down(size_t lines);

/**
 * Sets the color of the tty.
 * @param color The color to set the tty to.
 */
void tty_set_color(t_vga_entry_color color);

/**
 * Sets the cursor position.
 * @param x The new horizontal position of the cursor.
 * @param y The new vertical position of the cursor.
 */
void tty_set_cursor_pos(uint8_t x, uint8_t y);

/**
 * Sets the cursor type.
 * If the cursor type is set to CURSOR_TYPE_NONE, the cursor will be hidden.
 * @param type The type of cursor to use.
*/
void tty_set_cursor_type(t_cursor_type type);

/**
 * Flushs all changes to the tty.
 */
void tty_update();

/**
 * Writes data to the tty.
 * @param data The data to write to the tty.
 * @param size The size of the data to write to the tty.
 */
void tty_write(const char *data, size_t size);
