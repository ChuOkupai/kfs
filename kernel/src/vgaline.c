#include <vgaline.h>
#include <tty.h>

struct s_pool_vga_line		g_pools[MAX_WORKSPACES] = {0};


static inline void	fill_vga_line(struct s_list_vga_line *to_be_filled, t_vga_entry entry)
{
	for (size_t k = 0; k < VGA_WIDTH; k++)
		to_be_filled->line[k] = entry;
}

static inline void	clear_line(struct s_list_vga_line *to_be_filled)
{
	t_workspace				*w = tty_get_current_workspace();
	t_vga_entry				blank = vga_entry('\0', w->color);

	fill_vga_line(to_be_filled, blank);
}

static inline void	setup_to_alloc(void)
{
	for (size_t i = 0; i < MAX_WORKSPACES; i++)
	{
		if (g_pools[i].to_alloc == NULL)
		{
			for (size_t j = 0; j < POOL_SIZE; j++)
			{
				clear_line(g_pools[i].pool + j);
				if (j == POOL_SIZE - 1)
				{
					g_pools[i].pool[j].next = g_pools[i].pool;
					g_pools[i].pool->prev = g_pools[i].pool + j;
					continue ;
				}
				g_pools[i].pool[j].next = g_pools[i].pool + j + 1;
				g_pools[i].pool[j + 1].prev = g_pools[i].pool + j;
			}
			g_pools[i].to_alloc = g_pools[i].pool;
		}
	}
}

struct s_list_vga_line	*alloc_next_line(void) 
{
	struct s_pool_vga_line				*pool = g_pools + g_term->current_workspace;
	struct s_list_vga_line				*swap;

	if (pool->to_alloc == NULL)
		setup_to_alloc();
	swap = pool->to_alloc;
	pool->to_alloc = swap->next;
	if (pool->to_alloc->prev != swap)
		while (pool->to_alloc->prev != NULL)
			pool->to_alloc =pool->to_alloc->prev;
	swap = (struct s_list_vga_line *){0};
	return (swap);
}

void	free_line(struct s_list_vga_line *trash)
{
	struct s_pool_vga_line	*pool = NULL;
	for (size_t i = 0; i < MAX_WORKSPACES; i++)
	{
		if ((void *)trash >= (void *)((g_pools + i)->pool)
		&& (void *)trash < (void *)((g_pools + i)->pool + 1))
		{
			pool = g_pools + i;
			break ;
		}
	}
	if (!pool)
		return ;
	clear_line(trash);
	trash->next = pool->to_alloc;
	trash->prev = NULL;
	pool->to_alloc = trash;
}