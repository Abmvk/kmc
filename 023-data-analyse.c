#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char letter;
	int teken, teller = 0;

	printf("\n");

	if(argc!=3)
	{
		printf("Gebruik %s <bestandsnaam> <letter>\n", argv[0]);
		return 1;
	}

	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("Kan %s niet openen\n",argv[1]);
		return 1;
	}

	if(strlen(argv[2])!=1)
	{
		printf("Gebruik %s %s <letter>\n", argv[0], argv[1]);
		return 1;
	}

	letter = argv[2][0]>90 ? argv[2][0]-32 : argv[2][0];

	if(letter<'A'||letter>'Z')
	{
		printf("%c ligt buiten bereik, gebruik uitsluitend letters\n",argv[2][0]);
		return 1;
	}

	system("clear");

	do
	{
		teken=fgetc(fp);
		if(teken!=EOF)
		{
			printf("%c",teken);
			if((teken>90 ? teken-32 : teken)==letter) teller++;
		}
	} while(!feof(fp));
	fclose(fp);

	printf("\n----------------\nDe letter %c kwam %d keer voor, hoofdletter-ongevoelig\n\n",argv[2][0], teller);

return 0;
}
