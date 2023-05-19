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


int is_getal(const char* str);
void cell_set(const struct GameOfLife *game, int x, int y, bool aan);
void tekenVeld(const struct GameOfLife *game);
void maakVeld(struct GameOfLife *game);
void berekenNieuweGeneratie(struct GameOfLife *game);


int main(int argc, char **argv)
{
	struct GameOfLife game;
	bool pauze = true;
	int aantal = 1000, ch;

	if(argc > 1 && is_getal(argv[1]))
		aantal = atoi(argv[1]);

// scherm initialiseren
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();
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

// uitleg-scherm
	printw("\nWelkom bij Conway's Game of Life.\n\nHet \'spel\' speelt zich af op een oneindig veld van cellen die leven of niet leven.");
	printw(" Oneindigheid wordt benaderd doordat het hele scherm (of window)\nvan de terminal wordt gebruikt, en doordat het overloopt. ");
	printw("Dat betekent dat de cel helemaal links grenst aan de cel helemaal rechts, en net zo \nde cellen helemaal boven en onderaan ");
	printw("het scherm.\n\nIn eerste instantie kan je cellen aan en uit zetten. De cursor kan je daartoe verplaatsen met de q, a, o ");
	printw("en p-toetsen. Met de spatiebalk zet je de \ncel van de cursor aan of uit. Je kan ook met t aangeven dat je altijd wil ");
	printw("tekenen, met g dat je altijd wil gummen, en met b dat je weer een \nblanco-functie wil. Als je klaar bent druk je op enter.\n\n");
	printw("Daarna zal het programma zelf steeds nieuwe generaties berekenen en afbeelden. Als je achter life een aantal hebt opgegeven ");
	printw("dan wordt dat \naantal generaties uitgevoerd. Als je niets hebt opgegeven worden 1.000 generaties uitgevoerd. Als je geen ");
	printw("toets indrukt, pauzeert het \nprogramma tussen twee generaties. Druk je dan op f, dan wordt niet meer gepauzeerd.");
	printw("\n\n\nEr worden %d generaties berekend.    ", aantal);
	printw("\n\n\nDruk op een toets als je dit hebt begrepen.\n\n\n");
	getch();
	clear();

// teken het start-veld
	maakVeld(&game);


// bereken generaties
	do
	{
		berekenNieuweGeneratie(&game);
		tekenVeld(&game);
		move(0,0);
		printw("%d", aantal);
		if(pauze) ch = getch();
		if(ch == 'f') pauze = false;
	} while(--aantal > 0);

// scherm afsluiten voor einde programma
	move(0,0);
	printw("Dat waren alle generaties");
	getch();
	clear();
	refresh();
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


int is_getal(const char* str)
{
	if(str == NULL || *str == '\0')
		return 0;

	while(*str != '\0')
	{
		if(!isdigit(*str))
			return 0;
		str++;
	}

return 1;
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
	int teken = 0;

	while(!stoppen)
	{
		tekenVeld(game);
		move(x,y);
		if(game->veld[x][y][CELL_VELD])
			printw("#");
		else
			printw("_");
		move(x,y);
		ch = getch();

		switch(ch)
		{
			case 't':
				teken = 1;
				break;
			case 'g':
				teken = -1;
				break;
			case 'b':
				teken = 0;
				break;
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
		if(teken == 1)
			game->veld[x][y][CELL_VELD] = true;
		if(teken == -1)
			game->veld[x][y][CELL_VELD]= false;
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
