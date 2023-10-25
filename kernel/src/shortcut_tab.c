#include <keyboard.h>
#include <ps2.h>
#include <tty.h>
#include <stdio.h>
#include <stdbool.h>

t_keyboard_key pop_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH])
{
	if (SHORTCUTS_MAX_LENGTH < 1)
		return SCANCODE_NULL;
	t_keyboard_key value = tab[SHORTCUTS_MAX_LENGTH - 1];
	for(int i = SHORTCUTS_MAX_LENGTH - 1; i >= 0; i--)
	{
		if (i == 0)
			tab[0] = SCANCODE_NULL;
		else
			tab[i] = tab[i - 1];
	}
	return (value);
}

t_keyboard_key push_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH], t_keyboard_key value)
{
	if (SHORTCUTS_MAX_LENGTH < 1)
		return SCANCODE_NULL;
	for (int i = 0; i < SHORTCUTS_MAX_LENGTH; i++)
	{
		if (i == SHORTCUTS_MAX_LENGTH - 1)
			tab[i] = value;
		else
			tab[i] = tab[i + 1];
	}
	return (value);
}

void organize_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH])
{
	for (int i = SHORTCUTS_MAX_LENGTH; i >= 0; i--)
	{
		if (tab[i] == SCANCODE_NULL && i != 0)
		{
			tab[i] = tab[i - 1];
			tab[i - 1] = SCANCODE_NULL;
		}
	}
}

bool is_in_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH], t_keyboard_key value)
{
	for (int i = SHORTCUTS_MAX_LENGTH - 1; i >= 0; i--)
	{
		if (tab[i] == value)
			return (true);
	}
	return (false);
}

t_keyboard_key delete_stack_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH], t_keyboard_key value)
{
	for (size_t i = 0; i < SHORTCUTS_MAX_LENGTH; i++)
	{
		if (tab[i] == value)
		{
			tab[i] = SCANCODE_NULL;
		}
	}
	organize_keys(tab);
	return (value);
}