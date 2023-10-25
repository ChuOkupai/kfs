#include <keyboard.h>
#include <stdlib.h>

short g_modulator = 0;

void set_modulator(int pos, bool value)
{
    if (value)
    	g_modulator |= (1 << pos);
    else
        g_modulator &= ~(1 << pos);
}

bool get_modulator(int pos)
{
    return (g_modulator >> pos) & 1;
}

bool	printable_handler(t_keyboard_key code)
{
	char	*actual;
	char	*all[85] = {NULL, NULL, "1!s", "2@s", "3#s", "4$s", "5%s", "6^s", "7&s",
				"8*s", "9(s", "0)s", "-_s", "=+s", NULL, "\t\ts", "qQc", "wWc", "eEc", "rRc", "tTc", "yYc", "uUc", "iIc",
				"oOc", "pPc", "[{s", "]}s", NULL, NULL, "aAc", "sSc", "dDc", "fFc", "gGc", "hHc", "jJc", "kKc", "lLc", ";:s",
				"'\"s", "`~s", NULL, "\\\\s", "zZc", "xXc", "cCc", "vVc", "bBc", "nNc", "mMc", ",<s", ".>s", "/?s", NULL, "**s", NULL,
				"  s", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
				"77n", "88n", "99n", "--s", "44n", "55n", "66n", "++s", "11n", "22n", "33n", "00n", "..n"};
	if (code > 0x53 || all[code] == NULL)
		return (false);
	actual = all[code];
	if ((actual[2] == 'n' && get_modulator(KEYBOARDSTATE_NUMLOCK)))
		return (false);
	if ((actual[2] == 's' && get_modulator(KEYBOARDSTATE_SHIFT)) ||
		(actual[2] == 'c' && (get_modulator(KEYBOARDSTATE_SHIFT) ^ get_modulator(KEYBOARDSTATE_CAPSLOCK))))
		putchar(actual[1]);
	else
		putchar(actual[0]);
	return (true);
}