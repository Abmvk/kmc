/* Conway's Game of Life. Na uitleg van de werking kan de gebruiker een veld tekenen. Vervolgens berekent en tekent het programma een
aantal nieuwe generaties op basis van de regels van Life. Iedere generatie wordt in beeld gebracht. Dit proces wordt zo vaak herhaald als
door de gebruiker op de CLI opgegeven, met een default waarde van 1000.

De ncurses bibliotheek wordt gebruikt voor het plaatsen van de cursor op een opgegeven locatie, en voor het weergeven van een blokje voor
iedere levende cel.  */

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>			// nodig om het argument waarmee gestart wordt te testen op numerieke tekens
#include <ncurses.h>			// ncurses.h maakt stdio.h in dit geval overbodig

#define CELL_VELD 0			// het veld dat wordt weergegeven
#define COPIE_VELD 1			// een tijdelijk veld voor de berekening van de volgende generatie


struct GameOfLife			// In deze struct geven de functies steeds het te bewerken veld en de maximale omvang door
{					// het krijgt de vorm game.veld[x][y][CELL_VELD]
	bool ***veld;			// veld is een drie-dimensionale array van cellen die aan (true) of uit (false) staan
	int maxX;			// de hoogste waarde van x op het beschikbare scherm of terminal-window
	int maxY;			// de hoogste waarde van y op het beschikbare scherm of terminal-window
};



// De gebruikte functies:
// is_getal() controleert of het opgegeven argument van main een getal voorstelt
// cell_set() tekent of wist een cel op de opgegeven locatie, mits passend binnen de scherm-grootte
// maakVeld() laat de gebruiker een veld tekenen
// berekenNieuweGeneratie berekent op basis van de regels van Life de volgende generatie van een bestaand veld

int is_getal(const char* str);
void cell_set(const struct GameOfLife *game, int x, int y, bool aan);
void tekenVeld(const struct GameOfLife *game);
void maakVeld(struct GameOfLife *game);
void berekenNieuweGeneratie(struct GameOfLife *game);


int main(int argc, char **argv)
{
	struct GameOfLife game;		// game is de struct met daarin het Life-veld
	bool pauze = true;		// pauze bepaalt of de volgende generaties berekend worden met of zonder pauze
	int aantal = 1000, ch;		// aantal is het aantal te berekenen generaties, ch is een hulp-variabele

// als een argument is opgegeven en dit is een getal, dan wordt dat het aantal generaties
	if(argc > 1 && is_getal(argv[1]))
		aantal = atoi(argv[1]);

// scherm initialiseren
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();

// bepaal de omvang van het veld op basis van de maximale x- en y-coordinaat van het beschikbare scherm of window
	getmaxyx(stdscr, game.maxX, game.maxY);
	game.maxX--;
	game.maxY--;

// veld initialiseren: game.veld[x][y][VELD] wordt dynamisch gealloceerd
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


// bereken 'aantal' generaties, met pauze, tot gebruiker op f drukt. Linksboven loopt een teller van het aantal generaties dat nog komt
	do
	{
		berekenNieuweGeneratie(&game);
		tekenVeld(&game);
		move(0,0);
		printw("%d", aantal);
		refresh();
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


// veld vrij geven, immers met malloc() gealloceerd, dus moet nog free()
	for(int x = 0; x <= game.maxX; x++)
	{
		for(int y = 0; y <= game.maxY+1; y++)
		{
			free(game.veld[x][y]);
		}
		free(game.veld[x]);
	}
	free(game.veld);

return 0;
}


// op basis van de aangeleverde string wordt eerst bepaald of deze leeg is of direct afsluit, daarna karakter voor karakter testen of het
// een cijfer is. Zijn het alleen cijfers, dan is het dus een getal.
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

// de game struct wordt alleen meegeleverd zodat getest kan worden of x en y binnen de grenzen vallen. De functie verandert niets aan het
// veld. Alleen wordt op de gegeven coordinaat op het scherm een blokje geplaatst (spatie met atribuut REVERSE) of gewist (spatie)
void cell_set(const struct GameOfLife *game, int x, int y, bool aan)
{
	if(x<0 || x>game->maxX || y<0 || y>game->maxY)
		return;
	if(aan)
		mvaddch(x, y, ' ' | A_REVERSE);
	else
		mvaddch(x, y, ' ');
}


// de volledige array die het veld beschrijft wordt doorlopen, en per cel wordt de inhoud getekend of gewist, afhankelijk van de status
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

// hier wordt het veld gevuld en tegelijk getekend. De cursor start in het midden. Zolang de gebruiker niet op enter drukt wordt de loop
// herhaald. Deze loop bestaat uit het tekenen van het hele veld, het plaatsen van de cursor en deze veranderen op basis van de inhoud
// van die cel. Het programma moet zonder kleur kunnen werken, dus wordt de status van de cel onder de cursor met een karakter weergegeven
// vervolgens wordt het toetsenbord uitgelezen in ch. En met een switch wordt per relevante toets de actie bepaalt. Verplaatsen, tekenen,
// gummen, of geen actie. Hoewel de gebruiker ervaart dat hij "tekent" verandert hij in feite alleen de cellen. Het programma tekent
// vervolgens steeds het hele veld opnieuw
// De variabele 'teken' heeft een functie die lijkt op bool, maar kent drie statussen. -1 is wissen, 1 is tekenen, en 0 doet niets.
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


// Voor iedere cel moet op basis van het aantal levende buren bepaald worden of deze cel tot leven komt, blijft leven, of sterft.
// Omdat deze regel tegelijk voor alle cellen geldt, en dus niet binnen een generatie effect kan hebben op andere cellen wordt gewerkt
// met een copie-veld. Hier komt de status in de nieuwe generatie op basis van de buren uit de oude generatie. Als alle cellen zijn
// gedaan, wordt het hele copie-veld gekopieerd naar het actuele veld en is de nieuwe generatie dus de huidige generatie geworden
// Een extra complicerende factor is dat een veld volgens de regels onbegrensd moet zijn. Een praktische benadering is het veld ahw
// als bol te zien. Ga je verder naar links, rechts, boven of onder dan mogelijk, dan kom je aan de andere kant uit.
// Bij het tellen van het aantal buren mag de cel zelf niet meetellen, dus per cel worden 9 cellen geteld, met uitzondering van de cel zelf
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
