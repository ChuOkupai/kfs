#pragma once
# include <vga.h>
# include <tty.h>
struct s_list_vga_line
{
	t_vga_entry				line[VGA_WIDTH];
	struct s_list_vga_line*	prev;
	struct s_list_vga_line*	next;
};

# define POOL_SIZE 1000

struct s_pool_vga_line
{
	struct s_list_vga_line	pool[POOL_SIZE];
	struct s_list_vga_line	*start;
	struct s_list_vga_line	*to_alloc;
};
extern struct s_pool_vga_line		pools[MAX_WORKSPACES];
struct s_list_vga_line	*alloc_next_line(void);
void					free_line(struct s_list_vga_line *line);