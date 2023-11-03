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
 * @param fg Foreground color.
 * @param bg Background color.
 * @return A VGA color entry.
 */
inline t_vga_entry_color vga_entry_color(t_vga_color fg, t_vga_color bg) {
	return fg | bg << 4;
}

/**
 * Creates a VGA entry by combining a character and a color.
 * @param c Character.
 * @param color Color.
 * @return A VGA entry.
 */
inline t_vga_entry vga_entry(unsigned char c, t_vga_entry_color color) {
	return c | (t_vga_entry) color << 8;
}

/**
 * Fills the VGA buffer with a given character and color.
 * @param c The character to fill the buffer with.
 * @param color The color to fill the buffer with.
 */
void vga_fill(char c, t_vga_entry_color color);

/**
 * Puts a character at a given position in the VGA buffer.
 * @param c The character to put in the buffer.
 * @param color The color of the character.
 * @param x The x position of the character.
 * @param y The y position of the character.
 */
void vga_put(char c, t_vga_entry_color color, size_t x, size_t y);

/**
 * Puts a whole line at a given position in the VGA buffer.
 * @param entry The line to be print.
 * @param row The position on the screen to override.
 */
void vga_put_line(t_vga_entry entry[VGA_WIDTH], size_t row);
/**
 * Puts a rectangle of a given character and color at a given position in the VGA buffer.
 * @param c The character to put in the buffer.
 * @param color The color of the character.
 * @param x The x position of the character.
 * @param y The y position of the character.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
void vga_put_rect(char c, t_vga_entry_color color, size_t x, size_t y, size_t width, size_t height);

/**
 * compare two vga entries and return the substraction.
 * @param c1 The first character.
 * @param c2 The second character.
 */
uint16_t vga_entry_cmp(t_vga_entry c1, t_vga_entry c2);