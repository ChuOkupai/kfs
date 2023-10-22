#include <stdint.h>
#include <keyboard.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <stddef.h>

void ctrl1(void)
{
	puts("shrtct ctrl1");
}

int compare_shortcuts(const void *a, const void *b)
{
	const struct s_shortcut	*actual = (const struct s_shortcut	*) a;
	const struct s_shortcut	*ref = (const struct s_shortcut	*) b;

	for (size_t i = 0; i < SHORTCUTS_SEQUENCE; i++)
	{
		if (actual->code[i] != ref->code[i])
			return (actual->code[i] - ref->code[i]);
	}
	return (0);
}

// function that handle shortcuts, use the example of ctrl+1, by adding a struct s_shortcut inside the shortcuts array

bool shortcut_handler(uint8_t tab[SHORTCUTS_SEQUENCE])
{
	static struct s_shortcut actual = {0};
	bool					diff = false;
	struct s_shortcut *res = NULL;
	struct s_shortcut	shortcuts[1] = {
		{
			.code = {SCANCODE_NULL, SCANCODE_LEFT_CTRL, SCANCODE_1},
			.exec = ctrl1
		},
	};

	for (int i = 0; i < SHORTCUTS_SEQUENCE; i++)
	{
		if (actual.code[i] == tab[i])
			continue ;
		diff = true;
		actual.code[i] = tab[i];
	}
	if (!diff)
		return (false);
	res = bsearch((void*)&actual, (void*)shortcuts, sizeof(shortcuts) / sizeof(struct s_shortcut),
		sizeof(struct s_shortcut), compare_shortcuts);
	if (res)
	{
		res->exec();
		return (true);
	}
	return (false);
}

