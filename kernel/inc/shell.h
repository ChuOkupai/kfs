#pragma once
#include <stddef.h>

#define MAX_ARGS 128

typedef struct s_builtin {
	const char	*name;
	void		(*handler)(char**);
}	t_builtin;

/**
 * Dispatches a command to the appropriate builtin command handler.
 * @param args The command arguments array.
 * @return 0 on success, -1 otherwise.
*/
int builtin_exec(char **args);

/**
 * Parse a command string into a command structure.
 * @param args The command arguments array to fill, NULL terminated.
 * @param s The command string to parse.
 * @return 0 on success, -1 if too many arguments are provided.
*/
int parse_command(char *args[MAX_ARGS], char *s);

/**
 * Prints an error message to the terminal.
 * @param desc The error message to print.
*/
void print_error(const char *desc);
