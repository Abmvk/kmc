#include <stdio.h>						// standaard input/output functies
#include <stdlib.h>						// standaard C functies "allerlei"

int main()
{

	char voornaam[20], achternaam[30];
	int dag, maand, jaar;

	system("clear");					// roept het Linux/Bash-commando clear aan, om scherm te wissen.
	printf("Eerst maar eens het scherm leeg maken\n");	// werkt dus ALLEEN in Linux. Onder Windows CLS?

	printf("Voornaam: ");
	scanf("%19s", voornaam);				// zonder de 19 is iedere lengte mogelijk, maar voornaam is slechts 20 tekens
								// en dat gaat dus fout, de string moet met een NULL worden afgesloten

	printf("Achternaam: ");					// dit lijkt goed te gaan, bij een enkele achternama. Maar probeer eens
	scanf("%29s", achternaam);				// De Vries in te voeren.

	printf("Geboortejaar: ");
	scanf("%4d", &jaar);					// Let op: scanf heeft het adres nodig waar gegevens opgeslagen worden
	printf("Maand: ");					// dus de pointer naar de variabele, een & er voor
	scanf("%2d", &maand);
								// en nu met een beetje error-handling voor de dag
	printf("Dag: ");
	if(scanf("%2d", &dag)!=1)				// scanf() geeft een 1 als 1 gegeven is ingevoerd. Zo niet, is er iets mis
	{
		printf("Error: onjuiste input ontvangen\n");
		exit(1);					// dit is een soort tussentijdse return, maar nu met errorcode 1
	}

	printf("\n\n\Naam: %s %s\n", voornaam, achternaam);
	printf("Geboorte datum %d/%d/%d\n\n", dag, maand, jaar);
	


return 0;
}

