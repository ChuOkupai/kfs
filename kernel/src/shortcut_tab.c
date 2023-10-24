#include <keyboard.h>
#include <ps2.h>
#include <tty.h>
#include <stdio.h>
#include <stdbool.h>

uint8_t pop_keys(uint8_t tab[SHORTCUTS_MAX_LENGTH])
{
	if (SHORTCUTS_MAX_LENGTH < 1)
		return SCANCODE_NULL;
	uint8_t value = tab[SHORTCUTS_MAX_LENGTH - 1];
	for(int i = SHORTCUTS_MAX_LENGTH - 1; i >= 0; i--)
	{
		if (i == 0)
			tab[0] = SCANCODE_NULL;
		else
			tab[i] = tab[i - 1];
	}
	return (value);
}

uint8_t push_keys(uint8_t tab[SHORTCUTS_MAX_LENGTH], uint8_t value)
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

void organize_keys(uint8_t tab[SHORTCUTS_MAX_LENGTH])
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

bool is_in_keys(uint8_t tab[SHORTCUTS_MAX_LENGTH], uint8_t value)
{
	for (int i = SHORTCUTS_MAX_LENGTH - 1; i >= 0; i--)
	{
		if (tab[i] == value)
			return (true);
	}
	return (false);
}

uint8_t delete_stack_keys(uint8_t tab[SHORTCUTS_MAX_LENGTH], uint8_t value)
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