#include <stdio.h>
#include <stdlib.h>

/*

Het leest net iets logischer als het hoofdprogramma eerst komt, en de functies die je aanroept pas daarna. Maar voor de compiler is het
makkelijker als de functies worden gedeclareerd voor ze aangeroepen worden. De oplossing: eerst de functie declareren, dan main(), en daarna pas
de functies die je aan de voorkant gedeclareerd hebt daadwerkelijk definieren.

In dit programmaatje wordt de functie print_tekst() gedeclareerd voor main(), maar zonder body. Ook niet met {}, maar gewoon helemaal niet.

Na main() volgt dan de definitie van de functie print_tekst() alsnog, natuurlijk wel met exact dezelfde start als de eerdere declaratie!

*/

void print_tekst();

int main()
{
	print_tekst();
return 0;
}

void print_tekst()
{
	system("clear");
	printf("Dit is tekst\n");
}

