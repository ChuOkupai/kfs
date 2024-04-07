#include <key_sequence.h>
#include <string.h>

void key_sequence_append(t_key_sequence *seq, t_scancode key) {
	for (size_t i = 0; i < KEY_SEQUENCE_MAX_LENGTH; ++i)
		if (seq[i] == key)
			break;
		else if (!seq[i]) {
			seq[i] = key;
			break;
		}
}

int key_sequence_compare(const t_key_sequence *a, const t_key_sequence *b) {
	for (size_t i = 0; i < KEY_SEQUENCE_MAX_LENGTH; ++i)
		if (a[i] != b[i])
			return a[i] - b[i];
	return 0;
}

t_scancode key_sequence_last(const t_key_sequence *seq) {
	for (size_t i = 0; i < KEY_SEQUENCE_MAX_LENGTH; ++i)
		if (!seq[i])
			return seq[i - 1];
	return seq[KEY_SEQUENCE_MAX_LENGTH - 1];
}

void key_sequence_remove(t_key_sequence *seq, t_scancode key) {
	for (size_t i = 0; i < KEY_SEQUENCE_MAX_LENGTH; ++i)
		if (seq[i] == key) {
			memmove(seq + i, seq + i + 1,
				(KEY_SEQUENCE_MAX_LENGTH - i - 1) * sizeof(t_key_sequence));
			seq[KEY_SEQUENCE_MAX_LENGTH - 1] = 0;
			break;
		}

}
