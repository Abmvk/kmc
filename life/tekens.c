#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <ncurses.h>
#include "stdavk.h"



int main(int argc, char **argv)
{
	int x=0, y=0;
	int dx=1, dy=1;
	initscr();
	cbreak();
	noecho();
	for(int r=0;r<7000;r++)
	{
		mvaddch(x, y, ACS_BLOCK);
		refresh();
		x += dx;
		y += dy;
		if(x<1) dx=1;
		if(y<1) dy=1;
		if(x>45) dx=-1;
		if(y>138) dy=-1;
		for(int t=0;t<100000;t++){};
	}
	for(x=0;x<47;x++)
		for(y=0;y<140;y++)
			{
				for(int t=0;t<100000;t++){}
				mvaddch(x, y, ACS_BLOCK);
				refresh();
			}

	getch();
	endwin();

return 0;
}
