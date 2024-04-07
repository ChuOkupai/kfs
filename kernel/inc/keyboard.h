#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum e_scancode {
	SCANCODE_NULL				= 0x00,
	SCANCODE_ESC				= 0x01,
	SCANCODE_1					= 0x02,
	SCANCODE_2					= 0x03,
	SCANCODE_3					= 0x04,
	SCANCODE_4					= 0x05,
	SCANCODE_5					= 0x06,
	SCANCODE_6					= 0x07,
	SCANCODE_7					= 0x08,
	SCANCODE_8					= 0x09,
	SCANCODE_9					= 0x0A,
	SCANCODE_0					= 0x0B,
	SCANCODE_MINUS				= 0x0C,
	SCANCODE_EQUALS				= 0x0D,
	SCANCODE_BACKSPACE			= 0x0E,
	SCANCODE_TAB				= 0x0F,
	SCANCODE_Q					= 0x10,
	SCANCODE_W					= 0x11,
	SCANCODE_E					= 0x12,
	SCANCODE_R					= 0x13,
	SCANCODE_T					= 0x14,
	SCANCODE_Y					= 0x15,
	SCANCODE_U					= 0x16,
	SCANCODE_I					= 0x17,
	SCANCODE_O					= 0x18,
	SCANCODE_P					= 0x19,
	SCANCODE_LEFT_BRACKET		= 0x1A,
	SCANCODE_RIGHT_BRACKET		= 0x1B,
	SCANCODE_ENTER				= 0x1C,
	SCANCODE_LEFT_CTRL			= 0x1D,
	SCANCODE_A					= 0x1E,
	SCANCODE_S					= 0x1F,
	SCANCODE_D					= 0x20,
	SCANCODE_F					= 0x21,
	SCANCODE_G					= 0x22,
	SCANCODE_H					= 0x23,
	SCANCODE_J					= 0x24,
	SCANCODE_K					= 0x25,
	SCANCODE_L					= 0x26,
	SCANCODE_SEMICOLON			= 0x27,
	SCANCODE_APOSTROPHE			= 0x28,
	SCANCODE_GRAVE				= 0x29,
	SCANCODE_LEFT_SHIFT			= 0x2A,
	SCANCODE_BACKSLASH			= 0x2B,
	SCANCODE_Z					= 0x2C,
	SCANCODE_X					= 0x2D,
	SCANCODE_C					= 0x2E,
	SCANCODE_V					= 0x2F,
	SCANCODE_B					= 0x30,
	SCANCODE_N					= 0x31,
	SCANCODE_M					= 0x32,
	SCANCODE_COMMA				= 0x33,
	SCANCODE_PERIOD				= 0x34,
	SCANCODE_SLASH				= 0x35,
	SCANCODE_RIGHT_SHIFT		= 0x36,
	SCANCODE_KEYPAD_ASTERISK	= 0x37,
	SCANCODE_LEFT_ALT			= 0x38,
	SCANCODE_SPACE				= 0x39,
	SCANCODE_CAPS_LOCK			= 0x3A,
	SCANCODE_F1					= 0x3B,
	SCANCODE_F2					= 0x3C,
	SCANCODE_F3					= 0x3D,
	SCANCODE_F4					= 0x3E,
	SCANCODE_F5					= 0x3F,
	SCANCODE_F6					= 0x40,
	SCANCODE_F7					= 0x41,
	SCANCODE_F8					= 0x42,
	SCANCODE_F9					= 0x43,
	SCANCODE_F10				= 0x44,
	SCANCODE_NUM_LOCK			= 0x45,
	SCANCODE_SCROLL_LOCK		= 0x46,
	SCANCODE_KEYPAD_7			= 0x47,
	SCANCODE_KEYPAD_8			= 0x48,
	SCANCODE_KEYPAD_9			= 0x49,
	SCANCODE_KEYPAD_MINUS		= 0x4A,
	SCANCODE_KEYPAD_4			= 0x4B,
	SCANCODE_KEYPAD_5			= 0x4C,
	SCANCODE_KEYPAD_6			= 0x4D,
	SCANCODE_KEYPAD_PLUS		= 0x4E,
	SCANCODE_KEYPAD_1			= 0x4F,
	SCANCODE_KEYPAD_2			= 0x50,
	SCANCODE_KEYPAD_3			= 0x51,
	SCANCODE_KEYPAD_0			= 0x52,
	SCANCODE_KEYPAD_PERIOD		= 0x53,
	SCANCODE_F11				= 0x57,
	SCANCODE_F12				= 0x58,
	SCANCODE_PREV_TRACK			= 0x110,
	SCANCODE_NEXT_TRACK			= 0x119,
	SCANCODE_NUMPAD_ENTER		= 0x11C,
	SCANCODE_RIGHT_CTRL			= 0x11D,
	SCANCODE_MUTE				= 0x120,
	SCANCODE_CALCULATOR			= 0x121,
	SCANCODE_PLAY_PAUSE			= 0x122,
	SCANCODE_STOP				= 0x124,
	SCANCODE_VOLUME_DOWN		= 0x12E,
	SCANCODE_VOLUME_UP			= 0x130,
	SCANCODE_WEB_HOME			= 0x132,
	SCANCODE_KEYPAD_SLASH		= 0x135,
	SCANCODE_PRINT_SCREEN		= 0x137,
	SCANCODE_RIGHT_ALT			= 0x138,
	SCANCODE_HOME				= 0x147,
	SCANCODE_ARROW_UP			= 0x148,
	SCANCODE_PAGE_UP			= 0x149,
	SCANCODE_ARROW_LEFT			= 0x14B,
	SCANCODE_ARROW_RIGHT		= 0x14D,
	SCANCODE_END				= 0x14F,
	SCANCODE_ARROW_DOWN			= 0x150,
	SCANCODE_PAGE_DOWN			= 0x151,
	SCANCODE_INSERT				= 0x152,
	SCANCODE_DELETE				= 0x153,
	SCANCODE_LEFT_GUI			= 0x15B,
	SCANCODE_RIGHT_GUI			= 0x15C,
	SCANCODE_APPS				= 0x15D,
	SCANCODE_POWER				= 0x15E,
	SCANCODE_SLEEP				= 0x15F,
	SCANCODE_WAKE				= 0x163,
	SCANCODE_WEB_SEARCH			= 0x165,
	SCANCODE_WEB_FAVORITES		= 0x166,
	SCANCODE_WEB_REFRESH		= 0x167,
	SCANCODE_WEB_STOP			= 0x168,
	SCANCODE_WEB_FORWARD		= 0x169,
	SCANCODE_WEB_BACK			= 0x16A,
	SCANCODE_MY_COMPUTER		= 0x16B,
	SCANCODE_EMAIL				= 0x16C,
	SCANCODE_MEDIA_SELECT		= 0x16D
}	t_scancode;

typedef enum e_key_state {
	KEY_RELEASED,
	KEY_PRESSED
}	t_key_state;

typedef struct s_key {
	uint16_t scancode;
	t_key_state state;
}	t_key;

typedef enum e_modifier {
	MODIFIER_CAPS_LOCK = 1,
	MODIFIER_NUM_LOCK = 1 << 1,
	MODIFIER_SCROLL_LOCK = 1 << 2
}	t_modifier;

/**
 * Initializes the keyboard.
*/
void init_keyboard();

/**
 * Checks if a key is pressed.
 * @param scancode The scancode of the key to check.
 * @return True if the key is pressed, false otherwise.
*/
bool is_key_pressed(uint16_t scancode);

/**
 * Converts a scancode to an ASCII character.
 * If the scancode does not correspond to an ASCII character, 0 is returned.
 * @note The ASCII character can be non-printable.
 * @param scancode The scancode to convert.
 * @return The ASCII character corresponding to the scancode.
*/
char scancode_to_ascii(uint16_t scancode);

/**
 * Waits for a keypress.
 * Stores the key that was pressed in the key parameter.
 * @note This function is blocking.
 * @param key The key that was pressed.
 * @note This function is blocking.
*/
void wait_for_keypress(t_key *key);
