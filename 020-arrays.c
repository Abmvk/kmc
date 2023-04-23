#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *getal;
	int i, aantal, som = 0;

	system("clear");

	printf("Hoeveel getallen wil je optellen? ");
	scanf("%d", &aantal);
	printf("\n\n");

	getal = malloc( aantal * sizeof(int));

	for(i = 0; i<aantal; i++)
	{
		printf("geef getal %d: ", i+1);
		scanf("%d", &getal[i]);
	}

	printf("\n");

	for(i = 0; i<aantal; i++)
		som += getal[i];

	printf("De som van deze getallen is %d\n\n", som);

	free(getal);

return 0;
}
