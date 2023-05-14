#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <ncurses.h>
#include "stdavk.h"



int main(int argc, char **argv)
{
	int x, y;
	initscr();
	cbreak();
	noecho();
	for(x=0;x<10;x++)
		for(y=0;y<10;y++)
			mvaddch(10+x, 10+y, ACS_BLOCK);
	refresh();

	getch();
	endwin();

return 0;
}
