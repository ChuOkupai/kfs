#include <keyboard.h>
#include <ps2.h>
#include <tty.h>

void init_keyboard() {
	init_ps2();
	write_ps2_command(0xAE);
}

static t_keyboard_key push_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH], t_keyboard_key value)
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

static void organize_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH])
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

static bool is_in_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH], t_keyboard_key value)
{
	for (int i = SHORTCUTS_MAX_LENGTH - 1; i >= 0; i--)
	{
		if (tab[i] == value)
			return (true);
	}
	return (false);
}

static t_keyboard_key delete_stack_keys(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH], t_keyboard_key value)
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

void	handle_keyboard_input(void)
{
	static t_keyboard_key	on_pressed[SHORTCUTS_MAX_LENGTH] = {0};
	static bool				modifier = false;
	bool					shrtcut = false;
	t_keyboard_key 			scan_code = read_ps2_data();

	if (scan_code == SCANCODE_MODIFIER)
	{
		modifier = true;
		return ;
	}
	if (modifier)
		scan_code = scan_code | 0xff00;
	if ((scan_code & 0xff) > 0x80)
		delete_stack_keys(on_pressed, scan_code - 0x80);
	else if ((scan_code & 0xff) < 0x80 && !is_in_keys(on_pressed, scan_code))
	{
		push_keys(on_pressed, scan_code);
		shrtcut = shortcut_handler(on_pressed);
	}
	if (shrtcut || keyaction_handler(scan_code) || printable_handler(scan_code)){};
	if (modifier)
		modifier = false;
	return ;
}
