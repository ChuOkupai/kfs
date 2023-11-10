#include <vgaline.h>
#include <tty.h>

static inline t_pool_vga_line *get_pool_by_line_adress(void *line)
{
	struct s_pool_vga_line	*pool = NULL;
	t_workspace *ws = (t_workspace *)((term_storage()->workspaces));
	for (size_t i = 0; i < MAX_WORKSPACES; i++)
	{
		if (line >= (void *)(ws[i].allocator.pool)
			&& line < (void *)(ws[i].allocator.pool + 1))
		{
			pool = &(ws[i].allocator);
			break ;
		}
	}
	return pool;
}

void	vgaline_free(t_list_vga_line *trash)
{
	struct s_pool_vga_line	*pool = NULL;

	if (!(pool = get_pool_by_line_adress((void*)trash)))
		return ;
	vgaline_clear(trash);
	trash->next = pool->to_alloc;
	trash->prev = NULL;
	pool->to_alloc = trash;
}