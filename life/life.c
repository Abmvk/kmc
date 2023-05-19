#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <ncurses.h>
#include "stdavk.h"

#define CELL_VELD 0
#define COPIE_VELD 1

struct GameOfLife
{
	bool ***veld;
	int maxX;
	int maxY;
};

void cell_set(const struct GameOfLife *game, int x, int y, bool aan);
void tekenVeld(const struct GameOfLife *game);
void maakVeld(struct GameOfLife *game);
void berekenNieuweGeneratie(struct GameOfLife *game);

int main(int argc, char **argv)
{
	struct GameOfLife game;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	getmaxyx(stdscr, game.maxX, game.maxY);
	game.maxX--;
	game.maxY -= 2;

// veld initialiseren
	game.veld = malloc((game.maxX+2) * sizeof(bool **));
	for(int x = 0; x <= game.maxX; x++)
	{
		game.veld[x] = malloc((game.maxY+2) * sizeof(bool *));
		for(int y=0; y <= game.maxY; y++)
		{
			game.veld[x][y] = malloc(2 * sizeof(bool));
			game.veld[x][y][CELL_VELD] = false;
			game.veld[x][y][COPIE_VELD] = false;
		}
	}



	maakVeld(&game);

	do{
	berekenNieuweGeneratie(&game);
	tekenVeld(&game);
}while(getch()!='x');




// scherm afsluiten voor einde programma
	getch();
	endwin();

// veld vrij geven
	for(int x = 0; x <= game.maxX; x++)
	{
		for(int y = 0; y <= game.maxY+2; y++)
		{
			free(game.veld[x][y]);
		}
		free(game.veld[x]);
	}
	free(game.veld);

return 0;
}


void cell_set(const struct GameOfLife *game, int x, int y, bool aan)
{
	if(x<0 || x>game->maxX || y<0 || y>game->maxY)
		return;
	if(aan)
		mvaddch(x, y, ' ' | A_REVERSE);
	else
		mvaddch(x, y, ' ');
}

void tekenVeld(const struct GameOfLife *game)
{
	for(int x=0; x<=game->maxX; x++)
		for(int y=0; y<=game->maxY; y++)
		{
			bool cel = game->veld[x][y][CELL_VELD];
			cell_set(game, x, y, cel);
		};
	refresh();
}

void maakVeld(struct GameOfLife *game)
{
	int x=game->maxX / 2;
	int y=game->maxY / 2;
	int ch;
	bool stoppen = false;

	while(!stoppen)
	{
		tekenVeld(game);
		cell_set(game, x, y, !game->veld[x][y][CELL_VELD]);
		cell_set(game, x, y, game->veld[x][y][CELL_VELD]);
		ch = getch();

		switch(ch)
		{
			case 'q':
				if(x>0) x--;
				break;
			case 'a':
				if(x<game->maxX) x++;
				break;
			case 'o':
				if(y>0) y--;
				break;
			case 'p':
				if(y<game->maxY) y++;
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
	for (x=0; x<=game->maxX; x++)
		for(y=0; y<=game->maxY; y++)
			{
				buren = 0;
				for(i=x-1; i<=x+1; i++)
					for(j=y-1; j<=y+1; j++)
					{
						if(i == x && j == y)
							continue;
						xb = (i < 0) ? game->maxX : (i > game->maxX) ? 0 : i;
						yb = (j < 0) ? game->maxY : (j > game->maxY) ? 0 : j;
						if(game->veld[xb][yb][CELL_VELD]) buren++;
					}
				if(game->veld[x][y][CELL_VELD] && buren == 2)
					game->veld[x][y][COPIE_VELD] = true;
				if(buren > 3 || buren < 2)
					game->veld[x][y][COPIE_VELD] = false;
				if(buren == 3)
					game->veld[x][y][COPIE_VELD] = true;
			}
	for(x=0; x<=game->maxX; x++)
		for(y=0; y<=game->maxY; y++)
			game->veld[x][y][CELL_VELD] = game->veld[x][y][COPIE_VELD];
}
