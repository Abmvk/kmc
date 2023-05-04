#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stdavk.h"

typedef struct Node Node;

enum NodeType
{
	VRAAG,
	DIER
};

struct Node
{
	Node* ja;
	Node* nee;
	enum NodeType type;
	char vraag[256];
	char dier[256];
};

Node* createNode(enum NodeType type, const char* data)
{
	Node* node = malloc(sizeof(Node));
	node->ja = NULL;
	node->nee = NULL;
	node->type = type;

	if(type==VRAAG)
		strncpy(node->vraag, data, 256);
	else
		strncpy(node->dier, data, 256);

return node;
}

void printNode(Node* node)
{
	printf("%s", node->type ? node->dier : node->vraag);
}

bool ja_of_nee()
{
	char antw[255];
	bool resultaat = false;

	do
	{
		printf("Kies ja of nee: ");
		scanf("%s", antw);
	} while (strcmp(antw, "ja") != 0 && strcmp(antw, "nee") !=0);

	if(!strcmp(antw, "ja"))
		resultaat = true;

return resultaat;
}

int main()
{
	Node* root = createNode(VRAAG, "Is het een vogel?");
	Node* current = root;

	root->ja = createNode(DIER, "Kip");
	root->nee = createNode(DIER, "Konijn");

	cls();

	printf("%s\n",current->vraag);

	if(ja_of_nee())
	{
		if(current->ja != NULL)
			current = current->ja;
		else
			return 1;
	}
	else
	{
		if(current->nee != NULL)
			current = current->nee;
		else
			return 1;
	}

	printf("\n\n");

	if(current->type == VRAAG)
	{
		printf("%s\n",current->vraag);
		// herhalen tot er een dier komt
	}
	else
	{
		printf("Is het een %s?\n",current->dier);
		printf("\n\nIk heb %s\n\n", ja_of_nee() ? "Gewonnen!" : "Verloren!");
	}

return 0;
}

