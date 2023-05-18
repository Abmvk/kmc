#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <ncurses.h>
#include "stdavk.h"

#define MAX_X 45
#define MAX_Y 140
#define CELL_VELD 0
#define COPIE_VELD 1

struct GameOfLife
{
	bool veld[MAX_X+1][MAX_Y+1][2];
};

void cell_draw(int x, int y, bool aan);
void tekenVeld(const struct GameOfLife *game);
void maakVeld(struct GameOfLife *game);
//void berekenNieuweGeneratie(struct GameOfLife *game);

int main(int argc, char **argv)
{
	int x, y;
// scherm en veld initialiseren
	initscr();
	cbreak();
	noecho();
	struct GameOfLife game;
	for (x=0; x<=MAX_X; x++)
		for(y=0; y<=MAX_Y; y++)
			game.veld[x][y][0] = false;
// scherm klaar voor gebruik



	tekenVeld(&game);






// scherm afsluiten voor einde programma	
	getch();
	endwin();

return 0;
}


void cell_set(int x, int y, bool aan)
{
	if(x<0 || x>MAX_X || y<0 || y>MAX_Y)
		return;
	if(aan)
		mvaddch(x, y, ' ' | A_REVERSE);
	else
		mvaddch(x, y, ' ');
}

void tekenVeld(const struct GameOfLife *game)
{
	for(int x=0; x<=MAX_X; x++)
		for(int y=0; y<=MAX_Y; y++)
		{
			bool cel = game->veld[x][y][CELL_VELD];
			cell_set(x, y, cel);
		};
	refresh();
}

void maakVeld(struct GameOfLife *game)
{
	int x=MAX_X/2;
	int y=MAX_Y/2;






	
}
