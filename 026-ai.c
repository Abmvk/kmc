#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <json-c/json.h>
#include "stdavk.h"

#define TREE_FILE "vragen_tree.JSON"				// vragen_tree.JSON wordt gebruikt om de kennis-tree op te slaan

typedef struct Node Node;					// Node wordt de verkorte schrijfwijze van struct Node

struct Node
{
	Node* ja;						// De pointer naar de kind-node als het antwoord op de vraag ja is
	Node* nee;						// De pointer naar de kind-node als het antwoord op de vraag nee is
	enum NodeType
	{
		VRAAG,
		DING
	}  type;						// is de node een VRAAG of een DING?
	union
	{
		char vraag[256];
		char ding[256];
	} data;							// data bevat het ding of de vraag, afhankelijk van type
};

Node* createNode(enum NodeType type, const char* data);		// Maak een nieuwe node, met type en inhoud, geen kinderen

void writeNodeToJson(json_object *parent, Node *node);		// schrijft een node naar het JSON bestand

void writeTreeToFile(FILE* bestand, Node* node);		// schrijf een node naar bestand

Node* parseJSONNode(struct json_object* jsonNode);		// leest een node uit de JSON-file en maakt de node in de tree

Node* readTreeFromFile(FILE* bestand);				// lees een node uit het bestand

void save_tree(Node* tree);					// Schrijf de kennis-tree naar TREE_FILE

Node* init_tree();						// De kennis-tree wordt opgebouwd of van disk gelezen, als die bestaat

void free_tree(Node * root);					// geef geheugen van de tree vrij

bool ja_of_nee();						// Invoer ja of nee, andere input wordt gegefilterd. True bij ja, false bij nee



int main()
{
	bool geraden, goed_gegokt;				// geraden wordt true als computer raadt, goed_gegokt als dat goed was
	char nieuw_ding[256];					// als computer fout gokt, wordt hier het goede ding in opgevraagd
	int a, b;						// tellers voor het opschonen van antwoorden

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
								// alles omzetten naar kleine letters
			for(int i = 0; nieuw_ding[i] != '\0'; i++)
				nieuw_ding[i] = tolower(nieuw_ding[i]);
								// en alle tekens behalve letters er tussenuit
			for(a = 0, b = 0; nieuw_ding[a] != '\0'; a++)
				if(isalpha(nieuw_ding[a]))
					nieuw_ding[b++] = nieuw_ding[a];
			nieuw_ding[b] = '\0';

			printf("\nFormuleer nu een vraag waarmee ik %s had kunnen vinden. Zo gesteld, dat een ja tot", nieuw_ding);
			printf(" %s zou hebben geleid, in plaats van tot (een) %s.\n", nieuw_ding, current->data.ding);
								// de huidige gok verhuist naar de nee-child node
			current->nee = createNode(DING, current->data.ding);
								// de huidige node wordt een VRAAG, met de vraag van de gebruiker
			current->type = VRAAG;
			input("Wat is de vraag? ",current->data.vraag, sizeof(current->data.vraag));
								// alles behalve letters en spaties eruit, en naar kleine letters
			for(a=0, b=0; current->data.vraag[a] != '\0'; a++)
				if(isalpha(current->data.vraag[a]) || current->data.vraag[a] == ' ')
					current->data.vraag[b++] = tolower(current->data.vraag[a]);
								// vraagteken er achter, afsluiten met een \0 en beginnen met hoofdletter
			current->data.vraag[b++]='?';
			current->data.vraag[b]='\0';
			current->data.vraag[0]=toupper(current->data.vraag[0]);

								// tenslotte wordt de ja-child node het ding dat de gebruiker bedacht
			current->ja = createNode(DING, nieuw_ding);
		}

		printf("\nWil je nog eens spelen?\n");		// zolang de gebruiker blijft spelen groeit de kennis-tree
	} while(ja_of_nee());

	printf("\n");
	save_tree(root);					// als de speler is uitgespeeld moet de tree nog worden opgeslagen
	free_tree(root);

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

void writeNodeToJson(json_object *parent, Node *node)
{								//  nieuw json-object wordt gemaakt en gevuld met type, vraag/ding
	json_object *nodeObject = json_object_new_object();

	if(node->type == VRAAG)
	{
		json_object_object_add(nodeObject, "type", json_object_new_string("VRAAG"));
		json_object_object_add(nodeObject, "vraag", json_object_new_string(node->data.vraag));
								// als de child-nodes bestaan, worden die recursief ook naar json gezet
		if(node->ja != NULL)
		{
			json_object *jaObject = json_object_new_object();
			writeNodeToJson(jaObject, node->ja);
			json_object_object_add(nodeObject, "ja", jaObject);
		}

		if(node->nee != NULL)
		{
			json_object *neeObject = json_object_new_object();
			writeNodeToJson(neeObject, node->nee);
			json_object_object_add(nodeObject, "nee", neeObject);
		}
	}
	else if(node->type == DING)				// ding heeft geen children, dus alleen vullen
	{
		json_object_object_add(nodeObject, "type", json_object_new_string("DING"));
		json_object_object_add(nodeObject, "ding", json_object_new_string(node->data.ding));
	}
								// ieder object wordt ingepakt in een object "node"
	json_object_object_add(parent, "node", nodeObject);
}

Node* init_tree()
{
	FILE *bestand = fopen(TREE_FILE, "r");
	Node* start = NULL;

	if(bestand != NULL)					// als het bestand bestaat en leesbaar is, wordt het in de tree gelezen
	{
		start = readTreeFromFile(bestand);
		fclose(bestand);
	}
	else							// zo niet, dan worden een paar start-nodes opgezet
	{
		start = createNode(VRAAG, "Is het een dier?");
		start->ja = createNode(VRAAG, "Is het zwart?");
		start->nee= createNode(VRAAG, "Is het een gebouw?");

		Node* child = start->ja;
		child->ja = createNode(DING, "kraai");
		child->nee = createNode(DING, "hond");

		child = start->nee;
		child->ja = createNode(DING, "kerktoren");
		child->nee = createNode(DING, "bakpan");
	}

return start;
}

void writeTreeToFile(FILE* bestand, Node* node)
{								// alle nodes worden recursief in een json-object gezet en dan geschreven
	json_object *rootObject = json_object_new_object();
	writeNodeToJson(rootObject, node);

	const char *jsonString = json_object_to_json_string_ext(rootObject, JSON_C_TO_STRING_PRETTY);
	fprintf(bestand, "%s", jsonString);

	json_object_put(rootObject);
}

Node* readTreeFromFile(FILE* bestand)
{
	fseek(bestand, 0, SEEK_END);				// einde bestand wordt opgezocht
	long fileSize = ftell(bestand);				// de positie is nu dus de lengte
	rewind(bestand);					// positie terug naar begin

	char* buffer = (char *)malloc(fileSize+1);		// het hele bestand moet in een buffer passen, dus dynamisch alloceren
	if(buffer == NULL)
	{
		printf("Fout bij alloceren van geheugen!\n");
		return NULL;
	}

	if(fread(buffer, 1, fileSize, bestand) != fileSize)	// en het bestand lezen
	{
		printf("Fout bij het lezen van het bestand!\n");
		free(buffer);
		return NULL;
	}

	buffer[fileSize] = '\0';				// omdat het een string moet worden, afsluiten met een \0

	json_object* jsonObject = json_tokener_parse(buffer);	// string omzetten naar een voor json.h leesbaar object
	if(jsonObject == NULL)
	{
		printf("Fout bij het parsen van JSON!\n");
		free(buffer);
		return NULL;
	}

	Node* rootNode = parseJSONNode(jsonObject);		// hier wordt de hele tree opgebouwd en de root terug gegeven

	json_object_put(jsonObject);
	free(buffer);

return rootNode;
}

Node* parseJSONNode(struct json_object* jsonNode)
{
	Node* node = malloc(sizeof(Node));
	node->ja = NULL;
	node->nee = NULL;
								// eerst wordt een node gelezen, de waarden zitten daar in
	struct json_object* nodeObject = NULL;
	if(json_object_object_get_ex(jsonNode, "node", &nodeObject))
	{							// type wordt gelezen uit de sub van de node
		struct json_object* typeObject;
		if(json_object_object_get_ex(nodeObject, "type", &typeObject))
		{
			const char* typeString = json_object_get_string(typeObject);
			if(strcmp(typeString, "VRAAG") == 0)
			{
				node->type = VRAAG;

				struct json_object* questionObject;
				if(json_object_object_get_ex(nodeObject, "vraag", &questionObject))
				{
					const char* questionString = json_object_get_string(questionObject);
					strncpy(node->data.vraag, questionString, sizeof(node->data.vraag));
				}
			}
			else if(strcmp(typeString, "DING") == 0)
			{
				node->type = DING;

				struct json_object* thingObject;
				if(json_object_object_get_ex(nodeObject, "ding", &thingObject))
				{
					const char* thingString = json_object_get_string(thingObject);
					strncpy(node->data.ding, thingString, sizeof(node->data.ding));
				}
			}
		}
	}
								// nadat de data voor een node is ingelezen bekijken of child nodes bestaan
	struct json_object* jaObject;
	if(json_object_object_get_ex(nodeObject, "ja", &jaObject))
	{
		if(json_object_get_type(jaObject) == json_type_object)
		{						// en recursief wordt de ja-node gemaakt
			node->ja = parseJSONNode(jaObject);
		}
	}

	struct json_object* neeObject;
	if(json_object_object_get_ex(nodeObject, "nee", &neeObject))
	{
		if(json_object_get_type(neeObject) == json_type_object)
		{						// en de nee-node
			node->nee = parseJSONNode(neeObject);
		}
	}

return node;
}

void save_tree(Node* tree)
{
	FILE *bestand = fopen(TREE_FILE, "w");

	if(bestand == NULL )
	{
		printf("Kon het bestand niet openen voor schrijven!\n");
		return;
	}

	writeTreeToFile(bestand, tree);

	fclose(bestand);
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

void free_tree(Node * root)
{								// als alles gedaan is moet het geheugen van de tree nog vrij gegeven worden
	if(root==NULL)
		return;

	free_tree(root->ja);
	free_tree(root->nee);

	free(root);
}
