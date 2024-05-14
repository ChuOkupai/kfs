#include <ctype.h>
#include <shell.h>

static inline char *remove_ws(char *s) {
	for (; isspace(*s); ++s)
		*s = '\0';
	return s;
}

static inline size_t arglen(char *s) {
	char *p;
	for (p = s; *p && !isspace(*p); ++p);
	return p - s;
}

static inline char *skip_arg(char *s) {
	while (!isspace(*s))
		++s;
	return s;
}

char **shell_parse(char *s) {
	static char *args[MAX_ARGS + 1];

	for (size_t i = 0; 1; ++i) {
		if (i == MAX_ARGS)
			return NULL;
		s = remove_ws(s);
		size_t n = arglen(s);
		if (!n) {
			args[i] = NULL;
			break;
		}
		args[i] = s;
		s = s + n;
	}
	return args;
}
