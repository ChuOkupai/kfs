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
	const size_t 			limit = actual->size > ref->size ? ref->size : actual->size;

	for (size_t i = 0; i < limit; i++)
	{
		if (actual->code[i] != ref->code[i])
			return (actual->code[i] - ref->code[i]);
	}
	if (actual->size != ref->size)
	{
		if (actual->size < ref->size)
			return (1);
		else
			return (-1);
	}
	return (0);
}


// function that handle shortcuts, use the example of ctrl+1, by adding a struct s_shortcut inside the shortcuts array

bool shortcut_handler(uint8_t tab[SHORTCUTS_MAX_LENGTH])
{
	static struct s_shortcut	actual = {0};
	int							index_tab = -1;
	int							i = -1;
	size_t						size_new_actual;
	bool						diff = false;
	struct s_shortcut 			*res = NULL;
	struct s_shortcut			shortcuts[3] = {
		{
			.code = (uint8_t[]) {SCANCODE_LEFT_CTRL, SCANCODE_LEFT_SHIFT, SCANCODE_COMMA},
			.size = 3,
			.exec = tty_prev_workspace
		},
		{
			.code = (uint8_t[]) {SCANCODE_LEFT_CTRL, SCANCODE_LEFT_SHIFT, SCANCODE_PERIOD},
			.size = 3,
			.exec = tty_next_workspace
		}
	};

	while (++index_tab < SHORTCUTS_MAX_LENGTH)
	{
		if (tab[index_tab] == SCANCODE_NULL || actual.code[++i] == tab[index_tab])
			continue ;
		diff = true;
		actual.code[i] = tab[index_tab];
	}
	size_new_actual = ++i;
	if (!diff || size_new_actual < actual.size)
		return (false);
	actual.size = size_new_actual;

	res = bsearch((void*)&actual, (void*)shortcuts, sizeof(shortcuts) / sizeof(struct s_shortcut),
		sizeof(struct s_shortcut), compare_shortcuts);
	if (res)
	{
		res->exec();
		return (true);
	}
	return (false);
}

