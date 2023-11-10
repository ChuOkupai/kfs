#include <vga.h>
#include <vgaline.h>
#include <tty.h>
#include <stdio.h>

void	print_partial_screen(size_t row, t_list_vga_line *starting)
{
	for (; starting && row < VGA_HEIGHT; starting = starting->next)
		vga_put_line(starting->buff, row++);
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

static inline void	delete_line_chars(t_list_vga_line *line, size_t position, size_t len)
{
	size_t		index = position;
	t_vga_entry blank = vga_entry('\0', tty_get_current_workspace()->color);
	for (; index + len < VGA_WIDTH; index++)
		line->buff[index] = line->buff[index + len];
	for (; index < VGA_WIDTH; index++)
		line->buff[index] = blank;
}

static inline void recalibration(t_workspace *s) {

	size_t gap = 0;

	s->top_line = s->on_focus_line;
	while (gap++ < VGA_HEIGHT - 1 && s->top_line && s->top_line->prev)
		s->top_line = s->top_line->prev;
	s->row = gap - 1;
	print_partial_screen(0, s->top_line);
}

static inline void deletion_line_switch(t_workspace *s)
{
	t_list_vga_line	*relink;

	relink = s->on_focus_line->next;
	if (s->top_line == s->on_focus_line)
		s->top_line = s->on_focus_line->prev;
	s->on_focus_line = s->on_focus_line->prev;
	vgaline_free(s->on_focus_line->next);
	if (relink)
		relink->prev = s->on_focus_line;
	s->on_focus_line->next = relink;

}

static inline void	delete_char(t_workspace *s)
{
	if (s->column == 0)
	{
		if (!(s->on_focus_line->prev))
			return ;
		deletion_line_switch(s);
		s->column = get_last_char_column(s->on_focus_line);
		delete_line_chars(s->on_focus_line, s->column, 1);
		if (s->row != 0)
			s->row--;
	}
	else
		delete_line_chars(s->on_focus_line, --s->column, 1);
	print_partial_screen(0, s->top_line);
}

static inline void	newline_management_printing(t_workspace *s)
{
	t_list_vga_line	*control_line = s->top_line;
	t_list_vga_line	*new_line;

	s->column = 0;
	new_line = vgaline_alloc_safely();
	vgaline_link_line(new_line, s->on_focus_line);
	s->on_focus_line = new_line;
	if (control_line == s->top_line && ++s->row == VGA_HEIGHT) {
		s->row--;
		s->top_line = s->top_line->next;
	}
	if (control_line != s->top_line)
		print_partial_screen(0, s->top_line);
	else
		print_partial_screen(s->row, s->on_focus_line);
	return ;
}

static inline void	workspace_putc(t_workspace *s, char c)
{
	char to_be_put;
	if (vgaline_distance_between_lines(s->top_line, s->on_focus_line) > VGA_HEIGHT)
		recalibration(s);
	if (c == '\a')
		return delete_char(s);
	to_be_put = (c == '\n') ? ' ' : c;
	s->on_focus_line->buff[s->column++] = vga_entry(to_be_put, s->color);
	vga_put_line(s->on_focus_line->buff, s->row);
	if (s->column == VGA_WIDTH || c == '\n')
		newline_management_printing(s);
}

void tty_putc(char c) {
	workspace_putc(tty_get_current_workspace(), c);
}