
int iscntrl(int c) {
	return (c >= 0 && c < ' ') || c == 127;
}
