#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stdavk.h"

typedef struct Node Node;									// Node wordt de verkorte schrijfwijze van struct Node

enum NodeType												// Een Node van type VRAAG bevat een vraag en heeft twee kinderen
{															// Een Node van type DIER bevat een dier en heeft geen kinderen
	VRAAG,
	DIER
};

struct Node
{
	Node* ja;												// De pointer naar de kind-node als het antwoord op de vraag ja is
	Node* nee;												// De pointer naar de kind-node als het antwoord op de vraag nee is
	enum NodeType type;										// is de node een VRAAG of een DIER?
	char vraag[256];										// Als het een VRAAG-node is, staat hier de vraag
	char dier[256];											// Als het een DIER-node is, staat hier het dier
};

Node* createNode(enum NodeType type, const char* data);		// Maak een nieuwe node, met type en inhoud, geen kinderen
void printNode(Node* node);									// voor debug-doeleinden: zet inhoud node op het scherm
bool ja_of_nee();											// invoer ja of nee, andere input wordt gegefilterd. True bij ja, false bij nee

int main()
{
	Node* root = createNode(VRAAG, "Is het een vogel?");	// Start van de tree is een VRAAG
	Node* current = root;									// current wordt de pointer naar de actuele node

	root->ja = createNode(DIER, "Kip");						// eerste kind-node, bij ja is het een kip
	root->nee = createNode(DIER, "Konijn");					// tweede kind-node, bij nee is het een konijn

	cls();													// maak het scherm leeg

	printf("%s\n",current->vraag);							// stel de vraag uit de root-node. Bij loop, uit de actuele node

	if(ja_of_nee())											// vraag om een ja of nee op de vraag uit de actuele node
	{
		if(current->ja != NULL)								// test of er een ja-kind node is
			current = current->ja;							// en schuif de pointer door naar de ja-kind node
		else
			return 1;
	}
	else
	{
		if(current->nee != NULL)							// zoals hiervoor, maar dan voor de nee-kind node
			current = current->nee;
		else
			return 1;
	}

	printf("\n\n");

	if(current->type == VRAAG)								// als er een vraag klaar staat, moet die gesteld worden, en voorgaande
	{														// acties herhalen
		printf("%s\n",current->vraag);
		// herhalen tot er een dier komt
	}
	else
	{
		printf("Is het een %s?\n",current->dier);			// staat er een dier klaar, dan gokken op dat dier
		printf("\n\nIk heb %s\n\n", ja_of_nee() ? "Gewonnen!" : "Verloren!");
	}

return 0;
}

Node* createNode(enum NodeType type, const char* data)
{
	Node* node = malloc(sizeof(Node));						// alloceer geheugen voor een node
	node->ja = NULL;										// geen kind-nodes, dus beide pointers naar NULL
	node->nee = NULL;
	node->type = type;										// VRAAG of DIER

	if(type==VRAAG)											// afhankelijk van type moet de vraag[] of de dier[] gevuld
		strncpy(node->vraag, data, 256);
	else
		strncpy(node->dier, data, 256);

return node;
}

void printNode(Node* node)
{
	printf("%s", node->type ? node->dier : node->vraag);	// print de inhoud van de gevraagde node
}

bool ja_of_nee()
{
	char antw[255];											// de gebruiker voert een antwoord in, totdat dit ja of nee is
	bool resultaat = false;									// functie geeft true bij ja, en false bij nee

	do
	{
		printf("Kies ja of nee: ");
		scanf("%s", antw);
	} while (strcmp(antw, "ja") != 0 && strcmp(antw, "nee") !=0);

	if(!strcmp(antw, "ja"))
		resultaat = true;

return resultaat;
}