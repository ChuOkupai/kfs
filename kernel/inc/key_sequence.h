#pragma once
#include <keyboard.h>

#define KEY_SEQUENCE_MAX_LENGTH 4

typedef t_scancode t_key_sequence;

/**
 * Append a key to a key sequence if the sequence is not full.
 * If the key is already in the sequence, the function does nothing.
 * @param seq The key sequence.
 * @param key The key to append.
*/
void key_sequence_append(t_key_sequence *seq, t_scancode key);

/**
 * Compare two key sequences.
 * If the key sequences are equal, the function returns 0.
 * If a is less than b, the function returns a negative value.
 * Else, the function returns a positive value.
 * @param a The first key sequence.
 * @param b The second key sequence.
 * @return The comparison result.
*/
int key_sequence_compare(const t_key_sequence *a, const t_key_sequence *b);

/**
 * Get the last key of a key sequence.
 * @param seq The key sequence.
 * @return The last key of the sequence.
*/
t_scancode key_sequence_last(const t_key_sequence *seq);

/**
 * Removes a key from a key sequence.
 * If the key is not in the sequence, the function does nothing.
 * @param seq The key sequence.
 * @param key The key to remove.
*/
void key_sequence_remove(t_key_sequence *seq, t_scancode key);

