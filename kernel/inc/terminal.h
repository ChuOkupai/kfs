#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct s_screen {
	size_t row;
	size_t column;
	uint8_t color;
}	t_screen;

typedef struct s_terminal {
	t_screen screen;
}	t_terminal;

void terminal_clear(t_terminal *term);

void terminal_init(t_terminal *term);

void terminal_putc(t_terminal *term, char c);

void terminal_puts(t_terminal *term, const char *s);

void terminal_setcolor(t_terminal *term, uint8_t color);

void terminal_write(t_terminal *term, const char *data, size_t size);
