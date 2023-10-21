#include <stdio.h>
#include <tty.h>
 
int putchar(int ic) {
	char    c;
    tty_write(&c, 1);
    c = (char) ic;
	return ic;
}
