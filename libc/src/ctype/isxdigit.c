#include <ctype.h>

int isxdigit(int c)
{
	return isdigit(c) || (c >= 'a' && c < 'g') || (c >= 'A' && c < 'G');
}
