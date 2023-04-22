#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// nodig om met strings te werken
#include <stdbool.h>		// nodig voor boolean logica

struct Persoon {
	char naam[30];
	int leeftijd;
};

typedef struct {
	char naam[30];
	bool hond;
} Huisdier;

int main()
{
	struct Persoon bewoner;
	Huisdier dier[2];

	strcpy(bewoner.naam, "Kees Jansen");
	bewoner.leeftijd=76;

	system("clear");

	strcpy(dier[0].naam, "Bello");
	dier[0].hond = true;

	strcpy(dier[1].naam, "Blub");
	dier[1].hond = false;

	printf("We hebben een bewoner, hij heet %s en hij is %d jaar.\nHij neemt twee huisdieren mee, %s en %s.\n\n",
		bewoner.naam, bewoner.leeftijd, dier[0].naam, dier[1].naam);

	for(int i=0; i<2; i++)
		printf("%s is %s", dier[i].naam, dier[i].hond ? "een hond\n" : "geen hond\n");

	printf("\n\n");

return 0;
} 
