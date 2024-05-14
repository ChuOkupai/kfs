#pragma once
#include <stddef.h>

#define MAX_ARGS 128

extern int g_remaining_calls_to_bsod;

typedef struct s_builtin {
	const char	*name;
	void		(*handler)(char**);
}	t_builtin;

/**
 * Why not?
 * @note This function does not return.
*/
void bsod();

/**
 * Dispatches a command to the appropriate builtin command handler.
 * @param args The command arguments array.
 * @return 0 on success, -1 if the command is not found.
*/
int shell_exec(char **args);

/**
 * Parse a command string into a command arguments array.
 * @note The command string is modified in place.
 * @note The command arguments array is static and will be overwritten on the next call.
 * @note The command arguments array is NULL-terminated.
 * @note The command arguments array is limited to MAX_ARGS arguments.
 * @param s The command string to parse.
 * @return The command arguments array or NULL on error if there are too many arguments.
*/
char **shell_parse(char *s);

/**
 * Prints an error message to the terminal.
 * @param desc The error message to print.
*/
void shell_perror(const char *desc);

/**
 * Run the interactive shell.
 * This function does not return.
 */
void shell_run();
