#include <keyboard.h>
#include <ps2.h>
#include <tty.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int compare_keyascii_units(const void *a, const void *b)
{
	const struct keyaction	*actual = (const struct keyaction	*) a;
	const struct keyaction	*ref = (const struct keyaction	*) b;

	return (actual->code - ref->code);
}

void keyboardState_Shift (void)
{
	setmaj(KEYBOARDSTATE_SHIFT, !getmaj(KEYBOARDSTATE_SHIFT));
	return ;
}

void keyboardState_Capslock (void)
{
	setmaj(KEYBOARDSTATE_CAPSLOCK, !getmaj(KEYBOARDSTATE_CAPSLOCK));
	return ;
}

void keyboardState_Numslock (void)
{
	setmaj(KEYBOARDSTATE_NUMLOCK, !getmaj(KEYBOARDSTATE_NUMLOCK));
	return ;
}

void	backspace_action(void)
{
	printf("\nimplement backspace\n");
}

void	enter_action(void)
{
	putchar('\n');
}

bool	keyaction_handler(uint8_t code)
{
	struct keyaction 	actual = {.code = code};
	struct keyaction	*res;
	struct keyaction	keyactions[7] = {
		{
			.code = SCANCODE_BACKSPACE,
			.exec = backspace_action
		},
		{
			.code = SCANCODE_ENTER,
			.exec = enter_action
		},
		{
			.code = SCANCODE_LEFT_SHIFT,
			.exec = keyboardState_Shift
		},
		{
			.code = SCANCODE_RIGHT_SHIFT,
			.exec = keyboardState_Shift
		},
		{
			.code = SCANCODE_CAPS_LOCK,
			.exec = keyboardState_Capslock
		},
		{
			.code = SCANCODE_ANTI_LEFT_SHIFT,
			.exec = keyboardState_Shift
		},
		{
			.code = SCANCODE_ANTI_RIGHT_SHIFT,
			.exec = keyboardState_Shift
		}
	};

	res = bsearch((void*)&actual, (void*)keyactions, sizeof(keyactions) / sizeof(struct keyaction),
		sizeof(struct keyaction), compare_keyascii_units);
	if (res)
	{
		res->exec();
		return (true);
	}
	return (false);
}