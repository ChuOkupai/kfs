#pragma once
# include <vga.h>
# define POOL_SIZE 1024

typedef struct s_list_vga_line
{
	t_vga_entry				buff[VGA_WIDTH];
	struct s_list_vga_line*	prev;
	struct s_list_vga_line*	next;
}				t_list_vga_line;

typedef struct s_pool_vga_line
{
	t_list_vga_line	pool[POOL_SIZE];
	t_list_vga_line	*to_alloc;
}			  t_pool_vga_line;

/**
 * Return a line to write within it
*/
t_list_vga_line		*vgaline_alloc();

/**
 * Return a line to write within it and manage to change workspace fields (starting_line, top_line, on_focus_line) if the line allocated is an override
*/
t_list_vga_line		*vgaline_alloc_safely();

/**
 * Free the line passed as parameter
 * @param line the line to free
*/
void				vgaline_free(t_list_vga_line *line);

/**
 * Calculate the distance between 2 lines
 * return SIZE_MAX if error
 * @param start the starting line
 * @param end the ending line
*/
size_t				vgaline_distance_between_lines(t_list_vga_line *start, t_list_vga_line *end);

/**
 * Set a whole line with \0 as char and the workspace colors
 * @param to_be_clean the line to be clean
*/
void				vgaline_clear(t_list_vga_line *to_be_clean);

/**
 * link properly a newline to another line
 * @param new_line the new line
 * @param start the line to link to
*/
void				vgaline_link_line(t_list_vga_line *new_line, t_list_vga_line *start);