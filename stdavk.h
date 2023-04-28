#ifndef STDAVK_H
#define STDAVK_H


/* input-functie, return is 0 of 1 bij een fout. Argumenten zijn:
vraag: string die voor de input wordt gezet met printf()
inputs: de string waar de input uit stdin wordt opgeslagen
lengte: de maximale lengte van inputs

Alle invoer na lengte wordt genegeerd en uit de stdin stream gehaald
*/


int input(char vraag[], char inputs[], int lengte);


#endif // STDAVK_H
