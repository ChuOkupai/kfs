#pragma once
#include <vga.h>

#define MAX_WORKSPACES		3
#define TTY_WIDTH			VGA_WIDTH
#define TTY_HEIGHT			(VGA_HEIGHT - 1)
#define TTY_BUFSIZE			(TTY_WIDTH * TTY_HEIGHT)
#define TTY_DEFAULT_COLOR	vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK)

typedef enum e_cursor_type {
	CURSOR_TYPE_NONE = -1,
	CURSOR_TYPE_BLOCK = 0,
	CURSOR_TYPE_UNDERLINE = 14
}	t_cursor_type;

typedef struct s_workspace {
	uint16_t			buffer[TTY_BUFSIZE];
	char				last_command[TTY_BUFSIZE];
	uint16_t			rl_start;
	uint16_t			rl_cursor;
	t_vga_entry_color	color;
}	t_workspace;

typedef struct s_tty {
	t_workspace		workspaces[MAX_WORKSPACES];
	uint8_t			workspace_index;
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
 * Gets the color of the tty.
 * @return The color of the tty.
 */
t_vga_entry_color tty_get_color();

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
 * Moves the cursor to the end of the current line.
 */
void tty_move_end_of_line();

/**
 * Moves the cursor to the beginning of the current line.
 */
void tty_move_start_of_line();

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
 * Waits for the user to input a line.
 * @param prompt The prompt to display to the user.
 * @return The line input by the user.
*/
char *tty_readline(const char *prompt);

/**
 * The Elder Scrolls the tty one line up.
 */
void tty_scroll_up();

/**
 * Sets the color of the tty.
 * @param color The color to set the tty to.
 */
void tty_set_color(t_vga_entry_color color);

/**
 * Sets the cursor position.
 * @param i The index of the cursor position.
 */
void tty_set_cursor_position(uint16_t i);

/**
 * Sets the cursor type.
 * If the cursor type is set to CURSOR_TYPE_NONE, the cursor will be hidden.
 * @param type The type of cursor to use.
*/
void tty_set_cursor_type(t_cursor_type type);

/**
 * Sets the last command of the current workspace.
 * @param command The command to set as the last command.
*/
void tty_set_last_command(const char *command);

/**
 * Shows the last command of the current workspace.
 * @note The last command is only shown if the current line is empty.
*/
void tty_show_last_command();

/**
 * Flushs all changes to the tty.
 * This function should be called after all changes have been made to the tty.
 */
void tty_update();

/**
 * Writes data to the tty.
 * @param data The data to write to the tty.
 * @param size The size of the data to write to the tty.
 */
void tty_write(const char *data, size_t size);
