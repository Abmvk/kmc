#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

	printf("Naam: ");
	fgets(naam, sizeof(naam), stdin);	//een veilige variant op scanf, er wordt nooit meer gelezen dan in "naam" past

	if(strlen(naam)+1==sizeof(naam))	//als de gebruiker mogelijk meer dan de gevraagde lengte heeft ingevoerd
	{					//dan moet de stdin-buffer geleegd worden. Dat doen we byte voor byte tot de ASCII-code
		while(fgetc(stdin)!=10){}	//voor <enter> wordt gevonden. En dat is code 10.
	}

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

