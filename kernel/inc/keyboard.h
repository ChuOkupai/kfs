#pragma once

#define SCANCODE_NULL				0x00
#define SCANCODE_ESC				0x01
#define SCANCODE_1					0x02
#define SCANCODE_2					0x03
#define SCANCODE_3					0x04
#define SCANCODE_4					0x05
#define SCANCODE_5					0x06
#define SCANCODE_6					0x07
#define SCANCODE_7					0x08
#define SCANCODE_8					0x09
#define SCANCODE_9					0x0A
#define SCANCODE_0					0x0B
#define SCANCODE_MINUS				0x0C
#define SCANCODE_EQUALS				0x0D
#define SCANCODE_BACKSPACE			0x0E
#define SCANCODE_TAB				0x0F
#define SCANCODE_Q					0x10
#define SCANCODE_W					0x11
#define SCANCODE_E					0x12
#define SCANCODE_R					0x13
#define SCANCODE_T					0x14
#define SCANCODE_Y					0x15
#define SCANCODE_U					0x16
#define SCANCODE_I					0x17
#define SCANCODE_O					0x18
#define SCANCODE_P					0x19
#define SCANCODE_LEFT_BRACKET		0x1A
#define SCANCODE_RIGHT_BRACKET		0x1B
#define SCANCODE_ENTER				0x1C
#define SCANCODE_LEFT_CTRL			0x1D
#define SCANCODE_A					0x1E
#define SCANCODE_S					0x1F
#define SCANCODE_D					0x20
#define SCANCODE_F					0x21
#define SCANCODE_G					0x22
#define SCANCODE_H					0x23
#define SCANCODE_J					0x24
#define SCANCODE_K					0x25
#define SCANCODE_L					0x26
#define SCANCODE_SEMICOLON			0x27
#define SCANCODE_APOSTROPHE			0x28
#define SCANCODE_GRAVE				0x29
#define SCANCODE_LEFT_SHIFT			0x2A
#define SCANCODE_BACKSLASH			0x2B
#define SCANCODE_Z					0x2C
#define SCANCODE_X					0x2D
#define SCANCODE_C					0x2E
#define SCANCODE_V					0x2F
#define SCANCODE_B					0x30
#define SCANCODE_N					0x31
#define SCANCODE_M					0x32
#define SCANCODE_COMMA				0x33
#define SCANCODE_PERIOD				0x34
#define SCANCODE_SLASH				0x35
#define SCANCODE_RIGHT_SHIFT		0x36
#define SCANCODE_KP_ASTERISK		0x37
#define SCANCODE_LEFT_ALT			0x38
#define SCANCODE_SPACE				0x39
#define SCANCODE_CAPS_LOCK			0x3A
#define SCANCODE_F1					0x3B
#define SCANCODE_F2					0x3C
#define SCANCODE_F3					0x3D
#define SCANCODE_F4					0x3E
#define SCANCODE_F5					0x3F
#define SCANCODE_F6					0x40
#define SCANCODE_F7					0x41
#define SCANCODE_F8					0x42
#define SCANCODE_F9					0x43
#define SCANCODE_F10				0x44
#define SCANCODE_NUM_LOCK			0x45
#define SCANCODE_SCROLL_LOCK		0x46
#define SCANCODE_KP_7				0x47
#define SCANCODE_KP_8				0x48
#define SCANCODE_KP_9				0x49
#define SCANCODE_KP_MINUS			0x4A
#define SCANCODE_KP_4				0x4B
#define SCANCODE_KP_5				0x4C
#define SCANCODE_KP_6				0x4D
#define SCANCODE_KP_PLUS			0x4E
#define SCANCODE_KP_1				0x4F
#define SCANCODE_KP_2				0x50
#define SCANCODE_KP_3				0x51
#define SCANCODE_KP_0				0x52
#define SCANCODE_KP_PERIOD			0x53
#define SCANCODE_F11				0x57
#define SCANCODE_F12				0x58

#define SCANCODE_ANTI_LEFT_SHIFT	0xAA
#define SCANCODE_ANTI_RIGHT_SHIFT	0xB6

#define SCANCODE_UP_ARROW			0xFF48
#define SCANCODE_UP_SCROLL			0xFF49
#define SCANCODE_RIGHT_ARROW		0xFF4B
#define SCANCODE_LEFT_ARROW			0xFF4D
#define SCANCODE_DOWN_ARROW			0xFF50
#define SCANCODE_DOWN_SCROLL		0xFF51

#define SCANCODE_MODIFIER			0xe0
#define MODIFIER_LEFT_SHIFT			0x01
#define MODIFIER_RIGHT_SHIFT		0x02
#define MODIFIER_LEFT_CTRL			0x04
#define MODIFIER_RIGHT_CTRL			0x08
#define MODIFIER_LEFT_ALT			0x10
#define MODIFIER_RIGHT_ALT			0x20
#define MODIFIER_CAPS_LOCK			0x40
#define MODIFIER_NUM_LOCK			0x80

#define SHORTCUTS_MAX_LENGTH			3
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

typedef uint16_t t_keyboard_key;

extern short	g_modulator;

struct	s_shortcut
{
	t_keyboard_key 		*code;
	size_t				size;
	void				(*exec) (void);
};

struct	s_key_action
{
	t_keyboard_key		code;
	void				(*exec) (void);
};

enum	e_keyboard_state
{
	KEYBOARDSTATE_NUMLOCK,
	KEYBOARDSTATE_CAPSLOCK,
	KEYBOARDSTATE_SHIFT,
};

/**
 * Get the actual set of modulator (Shift, Numlock or Capslock) on the keyboard
 * @param pos The modulator to check - a element of the e_keyboard_state enum
*/
bool get_modulator(int pos);

/**
 * Set the actual set of modulator (Shift, Numlock or Capslock) on the keyboard
 * @param pos The modulator to check - a element of the e_keyboard_state enum
 * @param value The value to be set
*/
void set_modulator(int pos, bool value);


/**
 * Initializes the keyboard
*/
void	init_keyboard(void);

/**
 * Manage special key from the keyboard
 * @param code The last scancode catch
*/
bool	keyaction_handler(t_keyboard_key code);

/**
 * Manage every keyboard_input
 * This function is blocking.
*/
void	handle_keyboard_input(void);

/**
 * Manage special key from the keyboard
 * @param tab The last combination of keys pressed
*/
bool	shortcut_handler(t_keyboard_key tab[SHORTCUTS_MAX_LENGTH]);

/**
 * Manage special key from the keyboard
 * @param code The last key catched
*/
bool	printable_handler(t_keyboard_key code);
