#include <vgaline.h>
#include <tty.h>
#include <string.h>

static inline void set_actual_first_node(t_list_vga_line *node)
{
	while (node->prev != NULL)
		node = node->prev;
}

static inline void	setup_to_alloc(void)
{
	t_list_vga_line	*actual;
	t_workspace 	*ws = (t_workspace *) (term_storage()->workspaces);
	for (size_t i = 0; i < MAX_WORKSPACES; i++)
	{
		if (ws[i].allocator.to_alloc == NULL)
		{
			for (size_t j = 0; j < POOL_SIZE; j++)
			{
				actual = ws[i].allocator.pool + j;
				vgaline_clear(actual);
				if (j == POOL_SIZE - 1)
				{
					ws[i].allocator.pool[j].next = ws[i].allocator.pool;
					ws[i].allocator.pool->prev = ws[i].allocator.pool + j;
					continue ;
				}
				ws[i].allocator.pool[j].next = ws[i].allocator.pool + j + 1;
				ws[i].allocator.pool[j + 1].prev = ws[i].allocator.pool + j;
			}
			ws[i].allocator.to_alloc = ws[i].allocator.pool;
		}
	}
}

t_list_vga_line	*vgaline_alloc() 
{
	struct s_pool_vga_line		*allocator = &(tty_get_current_workspace()->allocator);
	t_list_vga_line				*swap;

	if (allocator->to_alloc == NULL)
	{
		setup_to_alloc();
		return vgaline_alloc();
	}
	swap = allocator->to_alloc;
	allocator->to_alloc = swap->next;
	if (allocator->to_alloc->prev != swap)
		set_actual_first_node(allocator->to_alloc);
	allocator->to_alloc->prev = NULL;
	memset(swap, 0, sizeof(t_list_vga_line));
	vgaline_clear(swap);
	return (swap);
}

t_list_vga_line *vgaline_alloc_safely()
{
	t_workspace *s = tty_get_current_workspace();
	t_list_vga_line *next = s->starting_line->next;
	t_list_vga_line	*newline = vgaline_alloc();
	if (newline == s->starting_line)
		s->starting_line = next;
	if (newline == s->top_line)
		s->top_line = s->starting_line;
	if (newline == s->on_focus_line)
		s->on_focus_line = s->starting_line;
	return newline;
}