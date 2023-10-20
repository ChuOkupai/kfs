#pragma once
#include <stddef.h>
#include <stdint.h>
#include <vga.h>

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
 */
void tty_clear();

/**
 * Initializes the tty.
 */
void tty_init();

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
