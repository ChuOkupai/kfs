#pragma once
#include <stddef.h>
#include <stdint.h>

#define VGA_MEMORY ((uint16_t*)0xB8000)
#define VGA_WIDTH ((size_t)80)
#define VGA_HEIGHT ((size_t)25)

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

inline uint8_t vga_entry_color(t_vga_color fg, t_vga_color bg) {
	return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char c, uint8_t color) {
	return c | (uint16_t) color << 8;
}

void vga_fill(char c, uint8_t color);

void vga_put(char c, uint8_t color, size_t x, size_t y);
