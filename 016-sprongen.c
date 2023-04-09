#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i=3;

	printf("\n\n eerste blok, i=3 \n\n");
	
	switch(i)
	{
		case 0:
			printf("\n case 0 \n");
		case 2:
			printf("\n case 2 \n");
		case 3:
			printf("\n case 3 \n");
		case 4:
			printf("\n case 4 \n");
		default:
			printf("\n default \n");
	}

	i=1;

	printf("\n\n tweede blok, i=1 \n\n");

	switch(i)
	{
		case 0:
			printf("\n case 0 \n");
		case 2:
			printf("\n case 2 \n");
		case 3:
			printf("\n case 3 \n");
		case 4:
			printf("\n case  4 \n");
		default:
			printf("\n default \n");
	}
	
	i=3;

	printf("\n\n derde blok, i=3 maar nu met break \n\n");

	switch(i)
	{
		case 0:
			printf("\n case 0 \n");
			break;
		case 2:
			printf("\n case 2 \n");
			break;
		case 3:
			printf("\n case 3 \n");
			break;
		case 4:
			printf("\n case 4 \n");
			break;
		default:
			printf("\n default \n");
			break;
	}

	printf("\n\n continue in een while loop, de 5 zou overgeslagen moeten worden: \n\n");

	i=0;
	while(i++<10)
	{
		if(i==5) continue;
		printf("%d\n",i);
	}

	printf("\n\n en nu met een goto hetzelfde effect als een break \n\n");

	i=0;
	while(i++<10)
	{
		if(i==5) goto label_escape;
		printf("%d\n",i);
	}

	label_escape:
	printf("\n\n we zijn uit de loop\n\n");

return 0;
}
