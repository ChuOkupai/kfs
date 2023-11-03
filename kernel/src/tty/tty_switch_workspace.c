#include <string.h>
#include <vgaline.h>
#include <tty.h>

static void workspace_switch(size_t next) {
	t_workspace		*next_w = term_storage()->workspaces + next;
	t_list_vga_line	*first_line = next_w->top_line;

	for (size_t i = 0; i < VGA_HEIGHT && first_line; i++)
	{
		memcpy(VGA_MEMORY + i * VGA_WIDTH, first_line->buff, VGA_WIDTH * sizeof(t_vga_entry));
		first_line = first_line->next;
	}
	term_storage()->current_workspace = next;
}

void tty_prev_workspace() {
	workspace_switch((term_storage()->current_workspace + MAX_WORKSPACES - 1) % MAX_WORKSPACES);
}

void tty_next_workspace() {
	workspace_switch((term_storage()->current_workspace + 1) % MAX_WORKSPACES);
}
