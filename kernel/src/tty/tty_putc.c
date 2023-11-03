#include <vga.h>
#include <vgaline.h>
#include <tty.h>
#include <stdio.h>

static inline void	print_partial_screen(size_t row, t_list_vga_line *starting)
{
	for (; starting && row < VGA_HEIGHT; starting = starting->next)
		vga_put_line(starting->buff, ++row);
	while (row < VGA_HEIGHT)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
			vga_put('\0', tty_get_current_workspace()->color, x, row);
		row++;
	}
}

static inline size_t	get_last_char_column(t_list_vga_line *line)
{
	size_t		i = VGA_WIDTH - 1;
	t_vga_entry	blank = vga_entry('\0', tty_get_current_workspace()->color);
	while (line->buff[i] == blank && i > 0)
		i--;
	return i;
}

static inline t_list_vga_line *allocate_surely()
{
	t_workspace *s = tty_get_current_workspace();
	t_list_vga_line *next = s->starting_line->next;
	t_list_vga_line	*newline = alloc_next_line();
	if (newline == s->starting_line)
		s->starting_line = next;
	if (newline == s->top_line)
		s->top_line = s->starting_line;
	if (newline == s->on_focus_line)
		s->on_focus_line = s->starting_line;
	return newline;
}

static inline void	workspace_putc(t_workspace *s, char c)
{
	t_list_vga_line	*actual_line = s->on_focus_line;
	t_list_vga_line	*top_line = s->top_line;
	t_list_vga_line	*new_line;

	if (c == '\a')
	{
		if (s->column == 0)
		{
			if (!(s->on_focus_line->prev))
				return ;
			s->column = get_last_char_column(s->on_focus_line->prev);
			if (s->top_line == s->on_focus_line)
				s->top_line = s->on_focus_line->prev;
			s->on_focus_line = s->on_focus_line->prev;
			free_line(s->on_focus_line->next);
			s->on_focus_line->next = NULL;
			if (s->column != 0)
				--s->column;
			s->on_focus_line->buff[s->column] = vga_entry('\0', s->color);
			if (s->row == 0)
			{
				print_partial_screen(0, s->top_line);
				return ;
			}
			s->row--;
		}
		else
			s->on_focus_line->buff[s->column--] = vga_entry('\0', s->color);
		vga_put_line(s->on_focus_line->buff, s->row);
		return ;
	}
	else
	{
		actual_line->buff[s->column] = vga_entry(c, s->color);
		vga_put(c, s->color, s->column++, s->row);
	}
	if (s->column == VGA_WIDTH || c == '\n')
	{
		s->column = 0;
		new_line = allocate_surely();
		link_nodes(new_line, s->on_focus_line);
		s->on_focus_line = new_line;
		if (++s->row == VGA_HEIGHT || distance_between_lines(s->top_line, new_line) == VGA_HEIGHT) {
			s->row--;
			s->top_line = s->top_line->next;
			print_partial_screen(0, s->top_line);
		}
		else if (top_line != s->top_line)
			print_partial_screen(0, s->top_line);
		else
			print_partial_screen(s->row, s->on_focus_line);
	}
}

void tty_putc(char c) {
	workspace_putc(tty_get_current_workspace(), c);
}
