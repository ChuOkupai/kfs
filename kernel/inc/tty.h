#pragma once
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

typedef struct s_screen {
	size_t row;
	size_t column;
	t_vga_entry_color color;
}	t_screen;

typedef struct s_tty {
	t_screen screen;
}	t_tty;

/**
 * Clears the tty, resetting the cursor position to the top left.
 * @param tty The tty to clear.
 */
void tty_clear(t_tty *tty);

/**
 * Initializes the tty.
 * @param tty The tty to initialize.
 */
void tty_init(t_tty *tty);

/**
 * Puts a character on the tty.
 * @param tty The tty to put the character on.
 * @param c The character to put on the tty.
 */
void tty_putc(t_tty *tty, char c);

/**
 * Puts a string on the tty.
 * @param tty The tty to put the string on.
 * @param s The string to put on the tty.
 */
void tty_puts(t_tty *tty, const char *s);

/**
 * Sets the color of the tty.
 * @param tty The tty to set the color of.
 * @param color The color to set the tty to.
 */
void tty_setcolor(t_tty *tty, t_vga_entry_color color);

/**
 * Writes data to the tty.
 * @param tty The tty to write to.
 * @param data The data to write to the tty.
 * @param size The size of the data to write to the tty.
 */
void tty_write(t_tty *tty, const char *data, size_t size);
