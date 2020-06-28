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

void printposition(int y, int x, char q) {
	move(y, x); 
	addch(q); 
}

void field(int max_Y, int max_X) { 
	for (int i = 0; i < max_Y + 2; i++) {
		printposition(i, 0, '0');
		printposition(i, max_X + 1, '0');	
	}
	
	for (int i = 0; i < max_X + 2; i++) {
		printposition(0, i, '0');
		printposition(max_Y + 1, i, '0');	
	}
	attron(COLOR_PAIR(1));
}

void drawsnake(struct position *snake, int d, char f) { 
	for (int i = 0; i < d; i++) {
		printposition(snake[i].y, snake[i].x, f);
	}
	refresh();
}

int main() {
	initscr(); 	   
	noecho(); 
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	curs_set(0); 
	nodelay(stdscr, TRUE);
	
	field(max_Y, max_X); 
	
	struct position snake[max_X * max_Y];
	struct food fod;
	int nextdir[2][4] = {{1,-1,0,0},{0,0,1,-1}};
	int d = 4;
	int ro = 0;
	
	for (int i = 0; i < d; i++) {
		snake[i].x = 5 + i;
		snake[i].y = 15;
		snake[i].symbol = '@';
	}

	drawsnake(snake, d, '@');
	refresh();
	
	endwin();
	return 0;
}
