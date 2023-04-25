#include <stdio.h>
#include <stdlib.h>

typedef struct node {					//via typedef maken we een type aan, node_t, waarmee nodes gemaakt kunnen worden
	int waarde;					//dit is de (simpele) inhoud van de node, in dit geval een int waarde
	struct node * volgende;				//de pointer volgende wijst naar de volgende node en is van het type node, dat kan in C
} node_t;						// node_t is de naam voor het type dat we gaan gebruiken

int main()
{
	node_t * kop = NULL;				// kop wordt de start van de list, ahw het anker waaraan de hele list hangt
	node_t * huidig = NULL;				// huidig wordt de pointer die over de list kan bewegen om elementen te vinden
	kop = (node_t *) malloc(sizeof(node_t));	// hier wordt de eerste node dynamisch in het geheugen gemaakt
	huidig = kop;					// en de pointer huidig wijst meteen naar de eerste en enige node in de list

	if(kop==NULL) return 1;				// altijd testen of malloc() geheugen heeft toegewezen, zo niet, stoppen met error 1

	kop->waarde = 1;				// de eerste node krijgt waarde 1
	kop->volgende = NULL;				// en omdat dit nog de laatste node is, is volgende een pointer naar NULL


	for( int i=0; i<10 ; i++)			// we gaan nu nieuwe nodes maken, 10 stuks
	{
		huidig->volgende = (node_t *) malloc(sizeof(node_t)); // met huidig->volgende wordt het element volgende uit de huidige struct
		huidig=huidig->volgende;			      // bedoeld. Met malloc() maken we een nieuwe node, en daarna schuiven we
		huidig->volgende = NULL;			      // huidig op, sluiten de list weer met een NULL en geven de laatste node
		huidig->waarde = i;				      // een waarde van i.

		if(huidig==NULL) return 1;			      // en weer testen of malloc() wel geheugen heeft toegewezen, anders error
	}

	system("clear");				// we gaan de list nu printen, dus eerst leeg scherm, en de pointer naar de huidige node
							// gaat terug naar de eerste node, die door kop wordt aangewezen
	huidig = kop;

	while(huidig != NULL)				// nu gaan we door de lijst lopen, totdat huidig naar de laatste node wijst, met NULL
	{
		printf("element->waarde is %d\n",huidig->waarde);
		huidig=huidig->volgende;		// en de pointer naar de huidige node schuift een node op
	}
							// de lijst is langer dan 10 elementen en begint niet met een 0. Is dat logisch? Ja!
return 0;
}
