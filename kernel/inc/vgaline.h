#pragma once
# include <vga.h>
typedef struct s_list_vga_line
{
	t_vga_entry				buff[VGA_WIDTH];
	struct s_list_vga_line*	prev;
	struct s_list_vga_line*	next;
}				t_list_vga_line;

# define POOL_SIZE 1000

typedef struct s_pool_vga_line
{
	t_list_vga_line	pool[POOL_SIZE];
	t_list_vga_line	*start;
	t_list_vga_line	*to_alloc;
}			  t_pool_vga_line;

t_list_vga_line		*alloc_next_line(void);
void				free_line(t_list_vga_line *line);
size_t				distance_between_lines(t_list_vga_line *start, t_list_vga_line *end);
inline void			link_nodes(t_list_vga_line *new_line, t_list_vga_line *start)
{
	t_list_vga_line *swap;
	if (new_line == start)
		return ;
	swap = start->next;
	new_line->prev = start;
	start->next = new_line;
	new_line->next = swap;
	if (new_line->next)
		new_line->next->prev = new_line;
}