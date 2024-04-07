#pragma once
#include <key_sequence.h>

typedef struct s_shortcut {
	t_key_sequence seq[KEY_SEQUENCE_MAX_LENGTH];
	void (*handler)(void);
}	t_shortcut;

/**
 * Dispatches a key sequence to the appropriate shortcut handler.
 * @param seq The key sequence to dispatch.
 * @return True if the key sequence was dispatched, false otherwise.
*/
bool shortcut_dispatch(t_key_sequence *seq);
