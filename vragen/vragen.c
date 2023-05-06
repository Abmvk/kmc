#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "stdavk.h"

#define TREE_FILE "vragen_tree"					// vragen_tree wordt gebruikt om de kennis-tree op te slaan

typedef struct Node Node;					// Node wordt de verkorte schrijfwijze van struct Node

typedef union							// Door een union te gebruiken, worden vragen en dingen over elkaar
{								// in het geheugen gezet. Dat scheelt 256 bytes per node
	char vraag[256];
	char ding[256];
} Data;

enum NodeType							// Een Node van type VRAAG bevat een vraag en heeft twee kinderen
{								// Een Node van type DING bevat een ding en heeft geen kinderen
	VRAAG,
	DING
};

struct Node
{
	Node* ja;						// De pointer naar de kind-node als het antwoord op de vraag ja is
	Node* nee;						// De pointer naar de kind-node als het antwoord op de vraag nee is
	enum NodeType type;					// is de node een VRAAG of een DING?
	Data data;						// data bevat het ding of de vraag, afhankelijk van type
};

Node* createNode(enum NodeType type, const char* data);		// Maak een nieuwe node, met type en inhoud, geen kinderen
Node* init_tree();						// De kennis-tree wordt opgebouwd of van disk gelezen, als die bestaat
void save_tree(Node* tree);					// Schrijf de kennis-tree naar TREE_FILE
bool ja_of_nee();						// Invoer ja of nee, andere input wordt gegefilterd. True bij ja, false bij nee

int main()
{
	bool geraden, goed_gegokt;				// geraden wordt true als computer raadt, goed_gegokt als dat goed was
	char nieuw_ding[256];					// als computer fout gokt, wordt hier het goede ding in opgevraagd

	Node* root = init_tree();				// root wordt de start van de tree
	Node* current;						// current is een pointer om door de tree te navigeren

	do							// spel wordt herhaald tot uitgespeeld == true
	{
		current = root;					// aan het begin van een ronde start de computer bij de root
		geraden = false;				// aan het begin is nog geen poging gedaan te raden

		cls();
		printf("Neem iets in gedachten, persoon, ding, etcetera. Ik zal vragen stellen en proberen te raden wat je in gedachten hebt.\n");
		printf("Antwoord op iedere vraag met ja of nee en sluit af met enter.\n\n");
		printf("Als ik het fout raad, kan je een ");
		printf("vraag invoeren waarmee ik het verschil tussen jouw \"iets\" en mijn gok had kunnen vinden, en jouw \"iets\".\n\n");
		printf("Neem iets in gedachten!\n\n");

		do
		{
			if(current->type == VRAAG)		// als een VRAAG klaar staat, wordt die gesteld om door de tree te navigeren
			{
				printf("\n%s\n", current->data.vraag);
				if(ja_of_nee())			// het antwoord (ja of nee) bepaalt de volgende node
					current = current->ja;
				else
					current = current->nee;
			}
			else					// als geen VRAAG klaar staat, staat er een DING klaar
			{
				geraden = true;			// dus de computer gaat nu dat ding gokken
				printf("\nIs het (een) %s?\n",current->data.ding);
			}
		} while(!geraden);				// herhalen tot een poging tot raden gedaan is

		goed_gegokt = ja_of_nee();			// de speler geeft aan of die gok goed was

		if(goed_gegokt)					// als de gok goed was is deze spelronde voorbij
			printf("\n\nHoera! Ik heb gewonnen!\n\n");
		else						// maar als de gok fout was moet een nieuwe tak gebouwd worden
		{
			printf("\n\nHelaas! Ik heb verloren!\n\n");
								// de gebruiker kan invoeren welk ding hij in gedachten had en een vraag
			input("Wat had je in gedachten? ",nieuw_ding, sizeof(nieuw_ding));

			printf("\nFormuleer nu een vraag waarmee ik %s had kunnen vinden. Zo gesteld, dat een ja tot", nieuw_ding);
			printf(" %s zou hebben geleid, in plaats van tot (een) %s.\n", nieuw_ding, current->data.ding);
								// de huidige gok verhuist naar de nee-child node
			current->nee = createNode(DING, current->data.ding);
								// de huidige node wordt een VRAAG, met de vraag van de gebruiker
			current->type = VRAAG;
			input("Wat is de vraag, eindigend met een vraagteken!\n",current->data.vraag, sizeof(current->data.vraag));
								// tenslotte wordt de ja-child node het ding dat de gebruiker bedacht
			current->ja = createNode(DING, nieuw_ding);
		}

		printf("\nWil je nog eens spelen?\n");		// zolang de gebruiker blijft spelen groeit de kennis-tree
	} while(ja_of_nee());

//	save_tree(root);					als de speler is uitgespeeld moet de tree nog worden opgeslagen

return 0;
}

Node* createNode(enum NodeType type, const char* gegevens)
{
	Node* node = malloc(sizeof(Node));			// alloceer geheugen voor een node
	node->ja = NULL;					// geen kind-nodes, dus beide pointers naar NULL
	node->nee = NULL;
	node->type = type;					// VRAAG of DING

	if(type==VRAAG)						// afhankelijk van type moet de vraag[] of de ding[] gevuld
		strncpy(node->data.vraag, gegevens, 256);
	else
		strncpy(node->data.ding, gegevens, 256);

return node;
}

Node* init_tree()
{
	FILE *bestand;
	Node* start;
	Node* child;

	bestand = fopen(TREE_FILE, "r");			// als het bestand TREE_FILE bestaat wordt hier de tree uitgelezen
	if(bestand != NULL)
	{
		cls();
		printf(TREE_FILE);
		printf(" bestaat al!\n");			// dat werkt nog niet, nu alleen een waarschuwing dat bestand bestaat
		fclose(bestand);
		abort();
	}
	else							// als TREE_FILE niet bestaat wordt een eerste ste nodes opgebouwd
	{
		start = createNode(VRAAG, "Is het een dier?");
		child = start;

		start->ja = createNode(VRAAG, "Is het zwart?");
		start->nee= createNode(VRAAG, "Is het een gebouw?");

		child = start->ja;

		child->ja = createNode(DING, "kraai");
		child->nee = createNode(DING, "hond");

		child = start->nee;

		child->ja = createNode(DING, "kerktoren");
		child->nee = createNode(DING, "bakpan");
	}

return start;							// in beide gevallen is het eindresultaat de pointer naar de start van de tree
}

void save_tree(Node* tree)					// deze functie moet de tree vanaf het startpunt gaan opslaan. Werkt nog niet
{
	FILE *bestand;
	bestand = fopen(TREE_FILE, "w");

	if(bestand != NULL)
	{
		printf("de root-vraag:\n%s\n", tree->data.vraag);
		fclose(bestand);
	}
	else
	{
		printf(TREE_FILE);
		printf(" openen is niet gelukt!\n");
		abort();
	}
}

bool ja_of_nee()
{
	char antw[255];						// de gebruiker voert een antwoord in, totdat dit ja of nee is
	bool resultaat = false;					// functie geeft true bij ja, en false bij nee

	do
	{
		input("Kies ja of nee: ", antw, sizeof(antw));
		for(int i = 0; antw[i] != '\0'; i++)
			antw[i] = tolower(antw[i]);
	} while (strcmp(antw, "ja") != 0 && strcmp(antw, "nee") !=0);

	if(!strcmp(antw, "ja"))
		resultaat = true;

return resultaat;
}
