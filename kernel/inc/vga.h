#pragma once
#include <stddef.h>
#include <stdint.h>

#define VGA_MEMORY	((uint16_t*)0xB8000)
#define VGA_WIDTH	((size_t)80)
#define VGA_HEIGHT	((size_t)25)
#define VGA_BUFSIZE	(VGA_WIDTH * VGA_HEIGHT)

/* Hardware text mode color constants. */
typedef enum e_vga_color {
	VGA_COLOR_BLACK,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_MAGENTA,
	VGA_COLOR_BROWN,
	VGA_COLOR_LIGHT_GREY,
	VGA_COLOR_DARK_GREY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_MAGENTA,
	VGA_COLOR_LIGHT_BROWN,
	VGA_COLOR_WHITE
}	t_vga_color;

typedef uint8_t t_vga_entry_color;
typedef uint16_t t_vga_entry;

/**
 * Creates a VGA color entry by combining foreground and background colors.
 * @param fg The foreground color.
 * @param bg The background color.
 * @return A VGA color entry.
 */
inline t_vga_entry_color vga_entry_color(t_vga_color fg, t_vga_color bg) {
	return fg | bg << 4;
}

/**
 * Creates a VGA entry by combining a character and a color.
 * @param c The character to display.
 * @param color The color of the character.
 * @return A VGA entry.
 */
inline t_vga_entry vga_entry(uint8_t c, t_vga_entry_color color) {
	return c | (t_vga_entry) color << 8;
}

/**
 * Fills a line in the VGA buffer with a given character and color.
 * @param c The character to fill the line with.
 * @param color The color to fill the line with.
 * @param y The line to fill.

 */
void vga_fill_line(char c, t_vga_entry_color color, size_t y);

/**
 * Fills the VGA buffer with a given character and color.
 * @param c The character to fill the buffer with.
 * @param color The color to fill the buffer with.
 */
void vga_fill(char c, t_vga_entry_color color);

/**
 * Gets a character at a given position in the VGA buffer.
 * @param x The x position of the character.
 * @param y The y position of the character.
 * @return The character at the given position.
*/
t_vga_entry vga_getc(size_t x, size_t y);

/**
 * Puts a character at a given position in the VGA buffer.
 * @param c The character to put in the buffer.
 * @param color The color of the character.
 * @param x The x position of the character.
 * @param y The y position of the character.
 */
void vga_putc(char c, t_vga_entry_color color, size_t x, size_t y);

/**
 * Puts a string at a given position in the VGA buffer.
 * @param s The string to put in the buffer.
 * @param color The color of the string.
 * @param x The x position of the string.
 * @param y The y position of the string.
 */
void vga_puts(const char *s, t_vga_entry_color color, size_t x, size_t y);

/**
 * Writes a whole line to the VGA buffer at a given row.
 * The line must be at least VGA_WIDTH characters long.
 * @param entry The line to write to the VGA buffer.
 * @param y The row to write the line to.
 */
void vga_write(const t_vga_entry *entry, size_t y);
