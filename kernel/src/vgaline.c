#include <vgaline.h>
#include <tty.h>

static inline void	fill_vga_line(t_list_vga_line *to_be_filled, t_vga_entry entry)
{
	for (size_t k = 0; k < VGA_WIDTH; k++)
		to_be_filled->line[k] = entry;
}

static inline void	clear_line(t_list_vga_line *to_be_filled)
{
	t_workspace				*w = tty_get_current_workspace();
	t_vga_entry				blank = vga_entry('\0', w->color);

	fill_vga_line(to_be_filled, blank);
}

static inline void set_actual_first_node(t_list_vga_line **node)
{
	while ((*node)->prev != NULL)
		(*node) =(*node)->prev;
	return ;
}

static inline t_pool_vga_line *get_pool_by_line_adress(void *line)
{
	struct s_pool_vga_line	*pool = NULL;
	for (size_t i = 0; i < MAX_WORKSPACES; i++)
	{
		if (line >= (void *)((g_term->workspaces[i].pool).pool)
			&& line < (void *)((g_term->workspaces[i].pool).pool + 1))
		{
			pool = g_term->workspaces[i].pool.pool;
			break ;
		}
	}
	return pool;
}

static inline void	setup_to_alloc(void)
{
	for (size_t i = 0; i < MAX_WORKSPACES; i++)
	{
		if (g_term->workspaces[i].pool.to_alloc == NULL)
		{
			for (size_t j = 0; j < POOL_SIZE; j++)
			{
				clear_line(g_term->workspaces[i].pool.pool + j);
				if (j == POOL_SIZE - 1)
				{
					g_term->workspaces[i].pool.pool[j].next = g_term->workspaces[i].pool.pool;
					g_term->workspaces[i].pool.pool->prev = g_term->workspaces[i].pool.pool + j;
					continue ;
				}
				g_term->workspaces[i].pool.pool[j].next = g_term->workspaces[i].pool.pool + j + 1;
				g_term->workspaces[i].pool.pool[j + 1].prev = g_term->workspaces[i].pool.pool + j;
			}
			g_term->workspaces[i].pool.to_alloc = g_term->workspaces[i].pool.pool;
		}
	}
}

t_list_vga_line	*alloc_next_line(void) 
{
	struct s_pool_vga_line		*pool = &(tty_get_current_workspace()->pool);
	t_list_vga_line				*swap;

	if (pool->to_alloc == NULL)
		setup_to_alloc();
	swap = pool->to_alloc;
	pool->to_alloc = swap->next;
	if (pool->to_alloc->prev != swap)
		set_actual_first_node(&(pool->to_alloc));
	swap = (t_list_vga_line *){0};
	return (swap);
}

void	free_line(t_list_vga_line *trash)
{
	struct s_pool_vga_line	*pool = NULL;

	if (!(pool = get_pool_by_line_adress((void*)trash)))
		return ;
	clear_line(trash);
	trash->next = pool->to_alloc;
	trash->prev = NULL;
	pool->to_alloc = trash;
}