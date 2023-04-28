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
