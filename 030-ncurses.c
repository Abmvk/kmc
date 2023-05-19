#include <stdio.h>
#include <ncurses.h>

int main()
{
	int x, y;
	initscr();
	cbreak();
	noecho();
	getmaxyx(stdscr, x, y);
	printw("x=%d\ny=%d", x, y);
	move(x/2, y/2);
	printw("Is dit het midden?");
	refresh();
	getch();
	endwin();

return 0;
}

