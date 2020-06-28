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
		printposition(i, 0, '#');
		printposition(i, max_X + 1, '#');	
	}
	
	for (int i = 0; i < max_X + 2; i++) {
		printposition(0, i, '#');
		printposition(max_Y + 1, i, '#');	
	}
	attron(COLOR_PAIR(1));
}

void drawsnake(struct position *snake, int d, char f) { 
	for (int i = 0; i < d; i++) {
		printposition(snake[i].y, snake[i].x, f);
	}
	refresh();
}

bool check(struct position cord, struct position *snake, int d) {
	for (int i = 0; i < d; i++) {
		if ((cord.x == snake[i].x) && (cord.y == snake[i].y))
		return true;
	}
	return false;
}

struct food foodcreate(struct food fod, int val, struct position *snake, int d) { 
	do {
		fod.cord.x = rand() % max_X + 1; 
		fod.cord.y = rand() % max_Y + 1;
	} while (check(fod.cord, snake, d)); 
	fod.value = val;
	char valc = val;
	printposition(fod.cord.y, fod.cord.x, valc + 48);
	refresh();
	return fod;
}

int main() {
	initscr(); 	   
	noecho(); 
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
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
	
	int dir1 = 1;
	struct position nextposition;
	int ch;
	
	fod = foodcreate(fod, rand() % 4 + 1, snake, d);
	
	bool gameover = false;
	
	while(!gameover) {
		ch = getch();
		dir1 = direction(ch,dir1); 
		nextposition.x = snake[0].x + nextdir[0][dir1]; 
		nextposition.y = snake[0].y + nextdir[1][dir1];
		if (nextposition.x > max_X)
			nextposition.x -= max_X;
		if (nextposition.x < 1)
			nextposition.x += max_X;
		if (nextposition.y > max_Y)
			nextposition.y -= max_Y;
		if (nextposition.y < 1)
			nextposition.y += max_Y;
		
		gameover = check(nextposition, snake, d);
		
		if (!gameover) {
			struct position lastposition;
			lastposition.x = snake[d - 1].x;
			lastposition.y = snake[d - 1].y;
			drawsnake(snake, d, ' ');
			for (int r = d - 1; r > 0; r--) {
				snake[r].x = snake[r-1].x;
				snake[r].y = snake[r-1].y;
			}
			if (ro > 0) {
				snake[d].x = lastposition.x;
				snake[d].y = lastposition.y;
				snake[d].symbol = '@';
				d++;
				ro--;
			}
			if ((fod.cord.x == snake[0].x) && (fod.cord.y == snake[0].y)) {
				ro += fod.value;
				fod = foodcreate(fod, rand()%4 + 1, snake, d);
			}
			snake[0].x = nextposition.x;
			snake[0].y = nextposition.y;
			drawsnake(snake, d, '@');
		}
		usleep(100000);
	}
	endwin();
	return 0;
}
