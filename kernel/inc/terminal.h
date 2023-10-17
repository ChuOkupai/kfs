#pragma once
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

typedef struct s_screen {
	size_t row;
	size_t column;
	t_vga_entry_color color;
}	t_screen;

typedef struct s_terminal {
	t_screen screen;
}	t_terminal;

/**
 * Clears the terminal, resetting the cursor position to the top left.
 * @param term The terminal to clear.
 */
void terminal_clear(t_terminal *term);

/**
 * Initializes the terminal.
 * @param term The terminal to initialize.
 */
void terminal_init(t_terminal *term);

/**
 * Puts a character on the terminal.
 * @param term The terminal to put the character on.
 * @param c The character to put on the terminal.
 */
void terminal_putc(t_terminal *term, char c);

/**
 * Puts a string on the terminal.
 * @param term The terminal to put the string on.
 * @param s The string to put on the terminal.
 */
void terminal_puts(t_terminal *term, const char *s);

/**
 * Sets the color of the terminal.
 * @param term The terminal to set the color of.
 * @param color The color to set the terminal to.
 */
void terminal_setcolor(t_terminal *term, t_vga_entry_color color);

/**
 * Writes data to the terminal.
 * @param term The terminal to write to.
 * @param data The data to write to the terminal.
 * @param size The size of the data to write to the terminal.
 */
void terminal_write(t_terminal *term, const char *data, size_t size);
