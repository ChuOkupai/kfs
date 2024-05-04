#pragma once
#include <stdint.h>

typedef struct s_stackframe t_stackframe;
struct s_stackframe {
	t_stackframe	*ebp;
	uint32_t		eip;
};

/**
 * Prints the stack information.
 */
void print_stack_info();

/**
 * Prints the stack trace.
 */
void print_stack_trace();

/**
 * Returns the size of the stack.
 * @return The size of the stack in bytes.
 */
size_t stack_size();
