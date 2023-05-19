
#include <stdio.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
	initscr();
	cbreak();
	noecho();
	printw("Hallo, wereld");
	refresh();
	getch();
	endwin();
	
return 0;
}

