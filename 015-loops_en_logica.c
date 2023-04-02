#include<stdio.h>
#include<stdlib.h>

int main()
{
	int t=0;
	
	while(t<10)
	{
		printf("while loop, t=%d\n",t++);
	}
	
	printf("\n\n");

	do
	{
		printf("do loop, t=%d\n", t--);
	} while(t>0);
	
	printf("\n\n");

	for(int x=0;x<10;x=t++)
	{
		printf("for loop, x=%d\n", x);
	}
	
	printf("\n\n");

	t=t>>2;
	
	printf("t twee bits shift rechts: %d\n", t);
	
	t=t<<2;
	
	printf("t twee bits shift links: %d\n", t);
	
	if(t==t || t++)
	{
		printf("\nt zou onveranderd moeten zijn: %d\n", t);
	}

	if(t==t && t++)
	{
		printf("\nt is nu %d, waarom?\n",t);
	}

	if(t=t && t++)
	{
		printf("\nWaarom is t nu: %d\n", t);
	}
	
return 0;
}
