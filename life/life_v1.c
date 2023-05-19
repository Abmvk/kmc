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
	bool veld[MAX_X][MAX_Y][2];
};

void cell_draw(int x, int y, bool aan);
void tekenVeld(const struct GameOfLife *game);
void maakVeld(struct GameOfLife *game);
void berekenNieuweGeneratie(struct GameOfLife *game);

int main(int argc, char **argv)
{
	int x, y;
// scherm en veld initialiseren
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	struct GameOfLife game;
	for (x=0; x<=MAX_X; x++)
		for(y=0; y<=MAX_Y; y++)
			game.veld[x][y][CELL_VELD] = false;
// scherm klaar voor gebruik


	maakVeld(&game);
	tekenVeld(&game);
	for(int test=0; test<100; test++){
	berekenNieuweGeneratie(&game);
	tekenVeld(&game);
getch();}




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
	int ch;
	bool stoppen = false;

	while(!stoppen)
	{
		tekenVeld(game);
		cell_set(x, y, !game->veld[x][y][CELL_VELD]);
		cell_set(x, y, game->veld[x][y][CELL_VELD]);
		ch = getch();

		switch(ch)
		{
			case 'q':
				if(x>0) x--;
				break;
			case 'a':
				if(x<MAX_X) x++;
				break;
			case 'o':
				if(y>0) y--;
				break;
			case 'p':
				if(y<MAX_Y) y++;
				break;
			case ' ':
				game->veld[x][y][CELL_VELD] = !game->veld[x][y][CELL_VELD];
				break;
			case '\n':
				stoppen = true;
				break;
			default:
				break;
		}
	}
}

void berekenNieuweGeneratie(struct GameOfLife *game)
{
	int x=0, y=0, buren, i, j, xb, yb;
	for (x=0; x<=MAX_X; x++)
		for(y=0; y<=MAX_Y; y++)
			{
				buren = 0;
				for(i=x-1; i<=x+1; i++)
					for(j=y-1; j<=y+1; j++)
					{
						if(i == x && j == y)
							continue;
						xb = (i < 0) ? MAX_X : (i > MAX_X) ? 0 : i;
						yb = (j < 0) ? MAX_Y : (j > MAX_Y) ? 0 : j;
						if(game->veld[xb][yb][CELL_VELD]) buren++;
					}
				if(game->veld[x][y][CELL_VELD] && buren == 2)
					game->veld[x][y][COPIE_VELD] = true;
				if(buren > 3 || buren < 2)
					game->veld[x][y][COPIE_VELD] = false;
				if(buren == 3)
					game->veld[x][y][COPIE_VELD] = true;
			}
	for(x=0; x<=MAX_X; x++)
		for(y=0; y<=MAX_Y; y++)
			game->veld[x][y][CELL_VELD] = game->veld[x][y][COPIE_VELD];
}
