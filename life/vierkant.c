#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <ncurses.h>
#include "stdavk.h"



int main(int argc, char **argv)
{
	initscr();
	cbreak();
	noecho();

	mvaddch(10, 10, ACS_BLOCK);

	refresh();

	getch();
	endwin();

return 0;
}
