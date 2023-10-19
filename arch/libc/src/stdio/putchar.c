#include "stdio.h"
#include "tty.h"
 
int putchar(int ic) {
	char    c;

    c = (char) ic;
    tty_write(&c, 1);
	return ic;
}