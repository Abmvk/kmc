Voor het gebruik van JSON heb ik de json-c bibliotheek toegevoegd. Om dit op Pi OS te doen zijn de volgende stappen nodig:

1. sudo apt-get install libjson-c-dev
2. Als je gebruik maakt van de Makefile of je werkt direct met gcc, voeg de parameter -ljson-c toe. In de Makefile in deze repo is dat al gedaan
3. In C toevoegen: #include <json-c/json.h>


je kan nu de functies uit deze bibliotheek gebruiken. Het bestand test_json.c kan je gebruiken om te testen of het werkt.

NB: de link optie in de Makefile kan geen kwaad als je geen JSON gebruikt. Dan wordt simpelweg niets uit de json-c bibliotheek toegevoegd.


