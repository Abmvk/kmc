
#include <stdio.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
	int x, y;
	initscr();
	cbreak();
	noecho();
	getmaxyx(stdscr, x, y);
	printw("x=%d\ny=%d", x, y);
	refresh();
	getch();
	endwin();
	
return 0;
}

