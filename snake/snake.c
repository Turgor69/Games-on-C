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
	struct position cord;
	int value;
};

int main() {
	initscr(); 	   
	noecho(); 
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	curs_set(0); 
	nodelay(stdscr, TRUE);
	endwin();
	return 0;
}
