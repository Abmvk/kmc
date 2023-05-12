/* simpel programmaaatje om de werking van gdb mee uit te proberen. Compileer met gcc gdb_ex.c -g, en start vervolgens met gdb -tui ./a.out

in gdb zet je een breakpoint met break main, en vervolgens starten met run. Daarna met next door het programma lopen, en met print kan je
de waardes van de verschillende variabelen zien. Als het goed is is c 0, en moet d=1/c dus een foutmelding geven. Maar dat gebeurt niet.

Met gdb kan je misschien zien wat er wel gebeurt?
*/

#include <stdio.h>

int main()
{
	int a=0, b=0;
	float c, d;

	for(; a<4; a++, b--)
	{
		printf("a=%d b=%d\n", a, b);
		c=a+b;
	}
	printf("\nc=%f &c=%p\n", c, &c);
	d=1/c;
	printf("\nd=%f\n",d);
return 0;
}
