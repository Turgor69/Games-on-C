#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct position {
	int x;
	int y;
	char symbol;
};

struct food {
	struct position line;
	int value;
};
