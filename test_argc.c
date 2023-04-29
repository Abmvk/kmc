/* test van argumenten voor een programma

argc geeft aantal argumenten, waaronder de programma-naam zelf (!), argv is een array van strings met daarin de argumenten zelf

*/

#include <studio.h>

int main(int argc, char *argv[])
{
	system("clear");
	for(int i=0;i<argc;i++)
		printf("%s\n",argv[i]);
return 0;
}