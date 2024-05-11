#include <ctype.h>
#include <shell.h>

static inline char *remove_ws(char *s) {
	for (; isspace(*s); ++s)
		*s = '\0';
	return s;
}

static inline char *get_next_arg(char *s) {
	for (s = remove_ws(s); isspace(*s); ++s)
		*s = '\0';
	return s;
}

static inline char *skip_arg(char *s) {
	while (!isspace(*s))
		++s;
	return s;
}

int parse_command(char *args[MAX_ARGS], char *s) {
	size_t i = 0;
	for (; i < MAX_ARGS - 1; ++i) {
		s = get_next_arg(s);
		if (!*s)
			break;
		args[i] = s;
		s = skip_arg(s);
	}
	if (i == MAX_ARGS - 1)
		return -1;
	args[i] = NULL;
	return 0;
}
