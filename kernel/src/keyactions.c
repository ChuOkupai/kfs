#include <keyboard.h>
#include <ps2.h>
#include <tty.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static int compare_keyascii_units(const void *a, const void *b)
{
	const struct s_key_action	*actual = (const struct s_key_action	*) a;
	const struct s_key_action	*ref = (const struct s_key_action	*) b;

	return (actual->code - ref->code);
}

void keyboard_state_shift (void)
{
	set_modulator(KEYBOARDSTATE_SHIFT, !get_modulator(KEYBOARDSTATE_SHIFT));
	return ;
}

void up_scrolling(void)
{
	if (tty_get_current_workspace()->top_line->prev)
	{
		tty_get_current_workspace()->top_line = tty_get_current_workspace()->top_line->prev;
		if (tty_get_current_workspace()->row < VGA_HEIGHT)
			tty_get_current_workspace()->row++;
		print_partial_screen(0, tty_get_current_workspace()->top_line);
	}
	return ;
}
void down_scrolling(void)
{
	if (tty_get_current_workspace()->top_line->next)
	{
		tty_get_current_workspace()->top_line = tty_get_current_workspace()->top_line->next;
		if (tty_get_current_workspace()->row > 0)
			tty_get_current_workspace()->row--;
		print_partial_screen(0, tty_get_current_workspace()->top_line);
	}
	return ;
}

void keyboard_state_capslock (void)
{
	set_modulator(KEYBOARDSTATE_CAPSLOCK, !get_modulator(KEYBOARDSTATE_CAPSLOCK));
	return ;
}

void keyboard_state_numslock (void)
{
	set_modulator(KEYBOARDSTATE_NUMLOCK, !get_modulator(KEYBOARDSTATE_NUMLOCK));
	return ;
}

void	enter_action(void)
{
	putchar('\n');
}

void	backspace_action(void)
{
	putchar('\a');
}

bool	keyaction_handler(t_keyboard_key code)
{
	struct s_key_action 	actual = {.code = code};
	struct s_key_action	*res;
	struct s_key_action	keys_actions[] = {
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
			.exec = keyboard_state_shift
		},
		{
			.code = SCANCODE_RIGHT_SHIFT,
			.exec = keyboard_state_shift
		},
		{
			.code = SCANCODE_CAPS_LOCK,
			.exec = keyboard_state_capslock
		},
		{
			.code = SCANCODE_NUM_LOCK,
			.exec = keyboard_state_numslock
		},
		{
			.code = SCANCODE_ANTI_LEFT_SHIFT,
			.exec = keyboard_state_shift
		},
		{
			.code = SCANCODE_ANTI_RIGHT_SHIFT,
			.exec = keyboard_state_shift
		},
		{
			.code = SCANCODE_UP_SCROLL,
			.exec = up_scrolling
		},
		{
			.code = SCANCODE_DOWN_SCROLL,
			.exec = down_scrolling
		},
	};
	res = bsearch((void*)&actual, (void*)keys_actions, sizeof(keys_actions) / sizeof(struct s_key_action),
		sizeof(struct s_key_action), compare_keyascii_units);
	if (res)
	{
		res->exec();
		return (true);
	}
	return (false);
}