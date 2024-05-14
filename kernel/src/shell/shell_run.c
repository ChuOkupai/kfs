#include <shell.h>
#include <tty.h>

void shell_run() {
	while (1) {
		char *buf = tty_readline("> ");
		char **args = shell_parse(buf);
		if (args) {
			if (!*args)
				continue;
			tty_set_last_command(buf);
			if (shell_exec(args) < 0)
				shell_perror("Command not found");
		}
		else
			shell_perror("Too many arguments");
	}
}
