#include <bitset.h>
#include <keyboard.h>
#include <ps2.h>

/**
 * Size of the bitset that represents the keys.
 * The index of the bitset is the scancode of the key.
 * If the scancode is and extended key, the 9th bit is set to 1 instead of 0xE0.
 * @note The size of the bitset is 512 because the scancode is a 9-bit value.
*/
#define KEYS_BITSET_SIZE BITSET_SIZE(512)

/** Set of keys that are defined. */
static const t_bitset g_defined_keys[KEYS_BITSET_SIZE] = {
	0xffffffff, 0xffffffff, 0x18fffff, 0,
	0xffffffff, 0xffffffff, 0x18fffff, 0,
	0x32010000, 0x1a54017, 0xf80fab80, 0x3fe8,
	0x32010000, 0x1a54017, 0xf80fab80, 0x3fe8
};

/** Set of keys that are currently pressed. */
static t_bitset g_key_state[KEYS_BITSET_SIZE] = { 0 };

/** Set of modifiers that are currently active. */
static uint8_t g_modifiers = 0;

/** ASCII table for the US keyboard layout with keypad keys. */
const uint8_t g_ascii_table[] = {
	0, 0, '1', '2', '3', '4', '5', '6',
	'7', '8', '9', '0', '-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
	'o', 'p', '[', ']', '\n', 0, 'a', 's',
	'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
	'\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/', 0, '*',
	0, ' ', 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, '-', 0, 0, 0, '+', 0,
	0, 0, 0, 0
};

/** ASCII table for the US keyboard layout when num lock is enabled. */
const uint8_t g_ascii_numlock[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, '7',
	'8', '9', 0, '4', '5', '6', 0, '1',
	'2', '3', '0', 0
};


/** ASCII table for the US keyboard layout when caps lock is enabled. */
const uint8_t g_ascii_shift[] = {
	0, 0, '!', '@', '#', '$', '%', '^',
	'&', '*', '(', ')', '_', '+', '\b', '\t',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
	'O', 'P', '{', '}', '\n', 0, 'A', 'S',
	'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
	'"', '~', 0, '|', 'Z', 'X', 'C', 'V',
	'B', 'N', 'M', '<', '>', '?', 0, '*',
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, '-', 0, 0, 0, '+', 0,
	0, 0, 0, '.'
};

/**
 * Check if any shift key is pressed.
 * @return True if the shift modifier is active, false otherwise.
*/
static bool is_shift_modifier_active() {
	return is_key_pressed(SCANCODE_LEFT_SHIFT) | is_key_pressed(SCANCODE_RIGHT_SHIFT);
}

/**
 * Check if the modifier key is pressed and update the modifier state.
 * @param scancode The scancode of the key.
*/
static void update_modifiers(uint16_t scancode) {
	if (scancode == SCANCODE_CAPS_LOCK)
		g_modifiers ^= MODIFIER_CAPS_LOCK;
	else if (scancode == SCANCODE_NUM_LOCK)
		g_modifiers ^= MODIFIER_NUM_LOCK;
	else if (scancode == SCANCODE_SCROLL_LOCK)
		g_modifiers ^= MODIFIER_SCROLL_LOCK;
}

void init_keyboard() {
	init_ps2();
	write_ps2_command(0xAE);
}

bool is_key_pressed(uint16_t scancode) {
	return bitset_is_set(g_key_state, scancode) != 0;
}

char scancode_to_ascii(uint16_t scancode) {
	if (scancode >= SIZEOF_ARRAY(g_ascii_table)) {
		if (scancode == SCANCODE_KEYPAD_ENTER)
			return '\n';
		if (scancode == SCANCODE_KEYPAD_SLASH)
			return '/';
		if (scancode == SCANCODE_DELETE)
			return 0x7F;
		return 0;
	}
	bool shift_modifier = is_shift_modifier_active();
	bool caps_lock = g_modifiers & MODIFIER_CAPS_LOCK;
	bool num_lock = !shift_modifier && (g_modifiers & MODIFIER_NUM_LOCK);
	char c;
	if (shift_modifier ^ caps_lock)
		c = g_ascii_shift[scancode];
	else
		c = g_ascii_table[scancode];
	if (!c && !shift_modifier && num_lock)
		c = g_ascii_numlock[scancode];
	return c;
}

void wait_for_keypress(t_key *key) {
	key->scancode = read_ps2_data();
	key->state = KEY_RELEASED;
	if (key->scancode == 0xE0)
		key->scancode = 0x100 | read_ps2_data();
	if (!bitset_is_set(g_defined_keys, key->scancode))
		key->scancode = SCANCODE_NULL;
	else if (key->scancode & 0x80) {
		key->scancode &= ~0x80;
		bitset_unset(g_key_state, key->scancode);
	} else {
		bitset_set(g_key_state, key->scancode);
		key->state = KEY_PRESSED;
		update_modifiers(key->scancode);
	}
}
