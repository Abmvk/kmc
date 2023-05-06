#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stdavk.h"

#define TREE_FILE "vragen_tree"					// vragen_tree wordt gebruikt om de kennis-tree op te slaan

typedef struct Node Node;					// Node wordt de verkorte schrijfwijze van struct Node

enum NodeType							// Een Node van type VRAAG bevat een vraag en heeft twee kinderen
{								// Een Node van type DIER bevat een dier en heeft geen kinderen
	VRAAG,
	DIER
};

struct Node
{
	Node* ja;						// De pointer naar de kind-node als het antwoord op de vraag ja is
	Node* nee;						// De pointer naar de kind-node als het antwoord op de vraag nee is
	enum NodeType type;					// is de node een VRAAG of een DIER?
	char vraag[256];					// Als het een VRAAG-node is, staat hier de vraag
	char dier[256];						// Als het een DIER-node is, staat hier het dier
};

Node* createNode(enum NodeType type, const char* data);		// Maak een nieuwe node, met type en inhoud, geen kinderen
Node* init_tree();						// de kennis-tree wordt opgebouwd of van disk gelezen, als die bestaat
void save_tree(Node* tree);
bool ja_of_nee();						// invoer ja of nee, andere input wordt gegefilterd. True bij ja, false bij nee

int main()
{
	bool geraden, goed_gegokt;
	bool uitgespeeld = false;
	char buffer[256];

	Node* root = init_tree();
	Node* current;

	do
	{
		current = root;
		geraden = false;

		cls();
		printf("Neem een dier in gedachten. Ik zal vragen stellen en proberen te raden wat je in gedachten hebt.\n");
		printf("Antwoord op iedere vraag met ja of nee, zonder hoofdletters, en sluit af met enter.\n\n");
		printf("Als ik het fout raad, kan je een ");
		printf("vraag invoeren waarmee ik het verschil tussen jouw dier en mijn gok had kunnen vinden, en de naam van je dier.\n\n");
		printf("Kies een dier!\n\n");


		do
		{
			if(current->type == VRAAG)
			{
				printf("\n%s\n", current->vraag);
				if(ja_of_nee())
					current = current->ja;
				else
					current = current->nee;
			}
			else
			{
				geraden = true;
				printf("\nIs het een %s?\n",current->dier);
			}
		} while(!geraden);

		goed_gegokt = ja_of_nee();

		if(goed_gegokt)
			printf("\n\nHoera! Ik heb gewonnen!\n\n");
		else
		{
			printf("\n\nHelaas! Ik heb verloren!\n\n");

			printf("Formuleer nu een vraag waarmee ik je dier had kunnen vinden. Zorg dat de vraag zo is gesteld, dat een ja tot");
			printf(" jouw dier zou hebben geleid.\n");

//			current->nee = createNode(DIER, current->dier);

			if(fgets(buffer, sizeof(buffer), stdin) != NULL)
			{
				size_t lengte = strlen(buffer);
				if(lengte>0 && buffer[lengte-1] == '\n')
				{
					buffer[lengte-1] = '\0';
					lengte--;
				}
			}

			printf("\n\nje vraag: %s\n\n", buffer);


		}

		printf("Wil je nog eens spelen?\n");
		uitgespeeld = !ja_of_nee();
	} while(!uitgespeeld);

	save_tree(root);

return 0;
}

Node* createNode(enum NodeType type, const char* data)
{
	Node* node = malloc(sizeof(Node));			// alloceer geheugen voor een node
	node->ja = NULL;					// geen kind-nodes, dus beide pointers naar NULL
	node->nee = NULL;
	node->type = type;					// VRAAG of DIER

	if(type==VRAAG)						// afhankelijk van type moet de vraag[] of de dier[] gevuld
		strncpy(node->vraag, data, 256);
	else
		strncpy(node->dier, data, 256);

return node;
}

Node* init_tree()
{
	FILE *bestand;
	Node* start;
	Node* child;

	bestand = fopen(TREE_FILE, "r");
	if(bestand != NULL)
	{
		cls();
		printf(TREE_FILE);
		printf(" bestaat al!\n");
		fclose(bestand);
		abort();
	}
	else
	{
		start = createNode(VRAAG, "Is het een vogel?");
		child = start;

		start->ja = createNode(VRAAG, "Is het zwart?");
		start->nee= createNode(VRAAG, "Is het een zoogdier?");

		child = start->ja;

		child->ja = createNode(DIER, "Kraai");
		child->nee = createNode(DIER, "Kip");

		child = start->nee;

		child->ja = createNode(DIER, "Konijn");
		child->nee = createNode(DIER, "Goudvis");
	}

return start;
}

void save_tree(Node* tree)
{
	FILE *bestand;
	bestand = fopen(TREE_FILE, "w");

	if(bestand != NULL)
	{
		printf("de root-vraag:\n%s\n", tree->vraag);
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
		printf("Kies ja of nee: ");
		scanf("%s", antw);
	} while (strcmp(antw, "ja") != 0 && strcmp(antw, "nee") !=0);

	if(!strcmp(antw, "ja"))
		resultaat = true;

return resultaat;
}
