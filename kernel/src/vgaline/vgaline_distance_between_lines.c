#include <vgaline.h>
#include <limits.h>

size_t	vgaline_distance_between_lines(t_list_vga_line *start, t_list_vga_line *end)
{
	size_t			size = 0;
	t_list_vga_line *actual = start;
	if (!start || !end)
		return (SIZE_MAX);
	while (actual != end && actual)
	{
		actual = actual->next;
		size++;
	}
	if (actual == end)
		return (size);
	return (SIZE_MAX);
}