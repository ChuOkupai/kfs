#include <keyboard.h>
#include <ps2.h>
#include <tty.h>

void	init_keyboard() {
	init_ps2();
	write_ps2_command(0xAE);
}

void	print_scancode(uint8_t code)
{
	char	hex[] = "0123456789abcdef";
	
	printf("scancode => 0x%c%c\n", hex[(code >> 4)], hex[(code & 0xf)]);
}

void	handle_keyboard_input(void)
{
	static uint8_t	on_pressed[SHORTCUTS_SEQUENCE] = {0};
	uint8_t 		scan_code = read_ps2_data();

	if (scan_code > 0x80)
		delete_stack_keys(on_pressed, scan_code - 0x80);
	else if (scan_code < 0x80 && !is_in_keys(on_pressed, scan_code))
		push_keys(on_pressed, scan_code);
	if (shortcut_handler(on_pressed) || keyaction_handler(scan_code) || printable_handler(scan_code)){};
}