#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{

	char naam[20], temp;
	int leeftijd, geboortejaar;
	time_t comp_tijd;
	struct tm *s_tijd;

	system("clear");

	printf("Leeftijd: ");
	scanf("%d",&leeftijd);
	scanf("%c", &temp);

	printf("Naam: ");
	fgets(naam, sizeof(naam), stdin);

	if(strlen(naam)+1==sizeof(naam)){while(fgetc(stdin)!=10){}}

	printf("Geboortejaar: ");
	scanf("%4d", &geboortejaar);

	printf("\n\nNaam: %s\nLeeftijd: %d\nGeboortejaar: %d\n\n", naam, leeftijd, geboortejaar);

	time(&comp_tijd);
	s_tijd = localtime(&comp_tijd);

	printf("\n%s",abs((s_tijd->tm_year+1900)-leeftijd-geboortejaar)>1 ? "Klopt je leeftijd wel?\n\n" : "Je leeftijd zou kunnen kloppen\n\n");

return 0;
}

