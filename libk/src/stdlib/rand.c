#include <stdlib.h>

static unsigned long g_state = 1;

int rand() {
	g_state = g_state * 1103515245 + 12345;
	return (unsigned int)(g_state / 65536) % 32768;
}

void srand(unsigned int seed) {
	g_state = seed;
}
