/* Dit programma leest het bestand BSN.txt, toetst per regel of een geldig bsn-nummer is opgenomen en schrijft de regels met een geldige bsn
vervolgens naar het bestand BSN-clean.txt
Regels met een ongeldig bsn worden op het gescherm genoemd.

Let op dat geen enkele controle plaats vindt op de juistheid van de ingelezen regels. Deze zijn van het vastgestelde format, maar als dat niet
zo zou zijn, zal dit programma het niet zien en dus onvoorspelbare uitkomsten geven.
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>				// om het type bool te gebruiken
#include "stdavk.h"				// voor de cls() functie

struct Record					// het bestand BSN.txt bevat records met drie velden:
{
	char regel[4];				// een regelnummer van 3 tekens, dus een string van 4 omdat er nog een \0 achter komt
	char bsn[12];				// het bsn-nummer met als format xxxx-xx-xxx, dus 11 tekens en een \0
	char code[6];				// een vijfletterige code
};

int main()
{
	FILE *fp, *fpw;				// fp wordt de filepointer naar het lees-bestand, fpw naar het schrijfbestand
	char buffer[255];			// een buffer om een regel uit het lees-bestand mee in te lezen
	char *token;				// dit wordt een pointer naar een deel van de buffer tot het eerste scheidingsteken < > of <tab>
	struct Record record;			// een record, opgebouwd uit de buffer
	int cijfer[10];				// de 9 cijfers van het bsn-nummer
	int elfproef;				// de som van de cijfers * hun positie, alleen positie 1 wordt met -1 vermenigvuldigd
	bool bsn;				// als elfproef deelbaar is door 11, dan is bsn true

	cls();

	if((fp = fopen("BSN.txt","r"))==NULL)	// BSN.txt is het bestand met de te controleren bsn-nummers
	{
		printf("Bestand BSN.txt kon niet geopend worden om te lezen\n");
		return 1;
	}

	if((fpw = fopen("BSN-clean.txt","w"))==NULL)	// BSN.clean.txt wordt het bestand waar alle mogelijke bsn-nummers in komen
	{
		printf("Bestand BSN-clean.txt kon niet geopend worden om te schrijven\n");
		return 1;
	}

	while(fgets(buffer, 255, fp)!=NULL)	// met fgets() wordt een regel gelezen, dat herhalen tot er geen regel meer komt
	{
		token=strtok(buffer, " \t");	// token wordt een pointer naar het eerste deel van buffer, tot een spatie of een tab
		strcpy(record.regel, token);	// record.regel wordt gevuld met de string token, dus eerste veld van de buffer
		token = strtok(NULL, " \t");	// de NULL is hier nodig, omdat strtok() verder gaat waar de vorige aanroep eindigde
		strcpy(record.bsn, token);
		token = strtok(NULL, " \t");
		strcpy(record.code, token);
		record.code[5]='\0';		// omdat de \n wordt meegelezen, moet deze nog vervangen worden door een \0

		cijfer[9]=record.bsn[0] -'0';	// dit deel kan niet met een loop, omdat het bsn-nummer in het bestand voorzien is van
		cijfer[8]=record.bsn[1] -'0';	// twee streepjes, dus xxxx-xx-xxx.
		cijfer[7]=record.bsn[2] -'0';	// het veld .bsn is een string, dus .bsn[x] is een char met een ASCII-code. Door daar
		cijfer[6]=record.bsn[3] -'0';	// '0' van af te trekken, krijg je de bijbehorende int waarde.
		cijfer[5]=record.bsn[5] -'0';
		cijfer[4]=record.bsn[6] -'0';	// de array cijfer[] loopt vanaf cijfer[0], maar omdat alle elementen straks vermenig-
		cijfer[3]=record.bsn[8] -'0';	// vuldigd gaan worden met hun positie in het nummer, is het handiger 0 over te slaan
		cijfer[2]=record.bsn[9] -'0';
		cijfer[1]=record.bsn[10]-'0';

		elfproef=0;			// de feitelijke 11-proef: de som van ieder cijfer * de positie wordt genomen, alleen
		for(int i = 2; i<10; i++)	// positie 1 wordt met -1 vermenigvuldig.
			elfproef += cijfer[i]*i;
		elfproef += cijfer[1]*-1;
		bsn = !(elfproef % 11);		// als elfproef deelbaar is door 11, is het een geldig bsn, dus elfproef % 11 == 0

		if(bsn)				// als het een bsn is, wordt het record geschreven naar BSN-clean.txt
			fprintf(fpw, "%s %s %s\n", record.regel, record.bsn, record.code);
		else				// als het geen bsn is, wordt het regelnummer op het scherm gezet
			printf("regel %s bevat een foutief BSN-nummer\n", record.regel);
	}

	fclose(fp);				// beide bestanden moeten nog gesloten worden
	fclose(fpw);

return 0;
}
