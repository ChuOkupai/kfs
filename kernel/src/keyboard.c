#include <keyboard.h>
#include <ps2.h>
#include <tty.h>

void	init_keyboard() {
	init_ps2();
	write_ps2_command(0xAE);
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