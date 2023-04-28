#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* input-functie, return is 0 of 1 bij een fout. Argumenten zijn:
vraag: string die voor de input wordt gezet met printf()
inputs: de string waar de input uit stdin wordt opgeslagen
lengte: de maximale lengte van inputs

Alle invoer na lengte wordt genegeerd en uit de stdin stream gehaald
*/


int input(char vraag[], char inputs[], int lengte)
{
	printf("%s",vraag);
	if(fgets(inputs,lengte, stdin)==NULL)
		return 1;
	if(strlen(inputs)+1==lengte)
		while(fgetc(stdin)!=10){}
return 0;			
}

int main()
{

	char naam[20], temp;			//temp hebben we nodig om de \n na leeftijd uit de stdin-buffer te verwijderen
	int leeftijd, geboortejaar;
	time_t comp_tijd;			//time_t is een type voor tijd/data-gegevens
	struct tm *s_tijd;			//struct tm * is een pointer naar een set tijd/data-gegevens

	system("clear");

	printf("Leeftijd: ");
	scanf("%d",&leeftijd);			//lees een int
	scanf("%c", &temp);			//lees de afsluitende \n en negeer die verder

	input("Naam: ",naam,20);

	printf("Geboortejaar: ");
	scanf("%4d", &geboortejaar);

	printf("\n\nNaam: %s\nLeeftijd: %d\nGeboortejaar: %d\n\n", naam, leeftijd, geboortejaar);

	time(&comp_tijd);			//niet belangrijk nu, wat gerommel met de tijd/data-functies van C. Time leest de huidige tijd
	s_tijd = localtime(&comp_tijd);		//localtime zet die naar de locale tijd in een struct, waarvan we tm_year gaan gebruiken
						//s_tijd->tm_year+1900 is het huidige jaar.

	printf("\n%s",abs((s_tijd->tm_year+1900)-leeftijd-geboortejaar)>1 ? "Klopt je leeftijd wel?\n\n" : "Je leeftijd zou kunnen kloppen\n\n");
						// a ? b : c = afhankelijk van a ofwel b, ofwel c.
return 0;
}

