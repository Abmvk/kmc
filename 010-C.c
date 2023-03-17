#include <stdio.h> //header file die je altijd wel nodig hebt

/* eerst een functie die twee integers optelt. 
Het resultaat wordt als uitkomst van de functie terug gegeven */

int tel_op(int a, int b)
{
	int r = a+b;
	return r;
}

int main()
{
	int a = 10;
	int b = 20;
	int som;
	som = tel_op(a,b);
	printf("De som van %d en %d is %d\n",a, b, som);
	return 0;
}

