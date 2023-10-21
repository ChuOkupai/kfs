#include <keyboard.h>
#include <ps2.h>
#include <tty.h>
#include <stdio.h>
#include <stdbool.h>

void init_keyboard() {
	init_ps2();

	// Enable the keyboard
	write_ps2_command(0xAE);
}

uint8_t pop_keys(uint8_t tab[3])
{
	uint8_t value = tab[2];
	tab[2] = tab[1];
	tab[1] = tab[0];
	tab[0] = SCANCODE_NULL;
	return (value);
}

uint8_t push_keys(uint8_t tab[3], uint8_t value)
{
	tab[0] = tab[1];
	tab[1] = tab[2];
	tab[2] = value;
	return (value);
}

void organize_keys(uint8_t tab[3])
{
	for (int i = 2; i >= 0; i--)
	{
		if (tab[i] == SCANCODE_NULL && i != 0)
		{
			tab[i] = tab[i - 1];
			tab[i - 1] = SCANCODE_NULL;
		}
	}
}

bool is_in_keys(uint8_t tab[3], uint8_t value)
{
	for (int i = 2; i >= 0; i--)
	{
		if (tab[i] == value)
			return (true);
	}
	return (false);
}

uint8_t delete_stack_keys(uint8_t tab[3], uint8_t value)
{
	for (size_t i = 0; i < 3; i++)
	{
		if (tab[i] == value)
		{
			tab[i] = SCANCODE_NULL;
		}
	}
	organize_keys(tab);
	return (value);
}

void	keyboard_handler(uint8_t scanCode)
{
	static uint8_t	onPressed[3] = {0};
	int 			code = scanCode;
	if (code > 0x80)
		delete_stack_keys(onPressed, scanCode - 0x80);
	else if (code < 0x80 && !is_in_keys(onPressed, scanCode))
		push_keys(onPressed, scanCode);
	shortcut_handler(onPressed);
}

void	print_scancode(uint8_t code)
{
	char hex[] = "0123456789abcdef";
	printf("scancode => 0x%c%c\n", hex[(code >> 4)], hex[(code & 0xf)]);
}

void handle_keyboard_input() {
	uint8_t scancode = read_ps2_data();
	// print_scancode(scancode);
	keyboard_handler(scancode);
}