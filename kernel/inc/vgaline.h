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

t_list_vga_line		*vgaline_alloc();
t_list_vga_line		*vgaline_alloc_safely();
void				vgaline_free(t_list_vga_line *line);
size_t				vgaline_distance_between_lines(t_list_vga_line *start, t_list_vga_line *end);
void				vgaline_clear(t_list_vga_line *to_be_filled);
void				vgaline_link_line(t_list_vga_line *new_line, t_list_vga_line *start);