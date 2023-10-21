#include <stdint.h>
#include <keyboard.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <stddef.h>


void zeroundeux(void)
{
	puts("shrtct 012");
}
void abc(void)
{
	puts("shrtct abc");
}
void ctrl1(void)
{
	puts("shrtct ctrl1");
}
void alt4(void)
{
	puts("shrtct alt4");
}
void wqf(void)
{
	puts("shrtct wqf");
}
void wqv(void)
{
	puts("shrtct wqv");
}

int compare_shortcuts(const void *a, const void *b)
{
	const struct shortcut	*actual = (const struct shortcut	*) a;
	const struct shortcut	*ref = (const struct shortcut	*) b;

	for (size_t i = 0; i < 3; i++)
	{
		if (actual->code[i] != ref->code[i])
			return (actual->code[i] - ref->code[i]);
	}
	return (0);
}
int aaa(const void *a, const void *b)
{
	(void)a;
	(void)b;
	return (-1);
}

void shortcut_handler(uint8_t tab[3])
{
	struct shortcut actual = {.code = {tab[0], tab[1], tab[2]}};
	struct shortcut *res = NULL;
	struct shortcut	shortcuts[6] = {
		{
			.code = {SCANCODE_NULL, SCANCODE_LEFT_CTRL, SCANCODE_1},
			.exec = ctrl1
		},
		{
			.code = {SCANCODE_NULL, SCANCODE_LEFT_ALT, SCANCODE_4},
			.exec = alt4
		},
		{
			.code = {SCANCODE_0, SCANCODE_1, SCANCODE_2},
			.exec = zeroundeux
		},
		{
			.code = {SCANCODE_W, SCANCODE_Q, SCANCODE_F},
			.exec = wqf
		},
		{
			.code = {SCANCODE_W, SCANCODE_Q, SCANCODE_V},
			.exec = wqv
		},
		{
			.code = {SCANCODE_A, SCANCODE_B, SCANCODE_C},
			.exec = abc
		}
	};
	res = bsearch((void*)&actual, (void*)shortcuts, sizeof(shortcuts) / sizeof(shortcuts[0]),
		sizeof(shortcuts[0]), compare_shortcuts);
	if (res)
		res->exec();
	return ;
}

