#include <vgaline.h>
#include <stdio.h>
#include <tty.h>

static inline t_workspace *get_workspace_by_line_adress(void *line)
{
	t_workspace *ws = (t_workspace *)((term_storage()->workspaces));
	for (size_t i = 0; i < MAX_WORKSPACES; i++)
	{
		if (line >= (void *)(ws + i)
			&& line < (void *)(ws + i + 1))
		{
			return (ws + i);
		}
	}
	return NULL;
}

void	vgaline_free(t_list_vga_line *trash)
{
	t_workspace	*ws = NULL;

	if (!(ws = get_workspace_by_line_adress((void*)trash)))
	{
		return ;
	}
	vgaline_clear(trash);
	trash->next = ws->allocator.to_alloc;
	trash->prev = NULL;
	ws->allocator.to_alloc = trash;
}