#include <stdint.h>
#include <keyboard.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <tty.h>

int compare_shortcuts(const void *a, const void *b)
{
	const struct s_shortcut	*actual = (const struct s_shortcut	*) a;
	const struct s_shortcut	*ref = (const struct s_shortcut	*) b;

	if (actual->size != ref->size)
	{
		if (actual->size < ref->size)
			return (1);
		else
			return (-1);
	}
	for (size_t i = 0; i < actual->size; i++)
		if (actual->code[i] != ref->code[i])
			return (actual->code[i] - ref->code[i]);
	return (0);
}

bool shortcut_handler(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH])
{
	static struct s_shortcut	actual = {0};
	int							index_tab = -1;
	int							i = -1;
	struct s_shortcut 			*res = NULL;
	struct s_shortcut			shortcuts[] = {
		{
			.code = (t_keyboard_key[]) {SCANCODE_LEFT_CTRL, SCANCODE_C},
			.size = 2,
			.exec = tty_clear
		},
		{
			.code = (t_keyboard_key[]) {SCANCODE_LEFT_CTRL, SCANCODE_RIGHT_ARROW},
			.size = 2,
			.exec = tty_next_workspace
		},
		{
			.code = (t_keyboard_key[]) {SCANCODE_LEFT_CTRL, SCANCODE_LEFT_ARROW},
			.size = 2,
			.exec = tty_prev_workspace
		}
	};

	while (++index_tab < SHORTCUTS_MAX_LENGTH)
	{
		if (tab[index_tab] == SCANCODE_NULL)
			continue ;
		actual.code[++i] = tab[index_tab];
	}
	actual.size = ++i;
	res = bsearch((void*)&actual, (void*)shortcuts, sizeof(shortcuts) / sizeof(struct s_shortcut),
		sizeof(struct s_shortcut), compare_shortcuts);
	if (res)
	{
		res->exec();
		return (true);
	}
	return (false);
}
