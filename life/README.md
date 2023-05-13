Doel van dit deelproject is de grafische mogelijkheden van de Pi uitproberen. Als project ga ik het spel "Life" van Conway proberen te maken. 

De logica daarachter is niet heel ingewikkeld, de uitdaging is vooral om het netjes op het scherm te krijgen. Een paar beperkingen:

1. Dit gaat niet werken via de iPad, omdat SSH/MOSH geen grafische weergave heeft, en VNC me hiervoor te ingewikkeld is voorlopig.
2. Ik heb geen idee of het buiten Linux werkt. Goede kans dat het niet eens werkt op andere beeldschermen dan het mijne. Wie er dus iets mee wil
doen zal daar zelf oplossingen voor moeten zoeken.
3. Voor gebruik van de grafische mogelijkheden heb ik de libbsd-dev bibliotheek geinstalleerd met

sudo apt-get install libbsd-dev


En vanaf daar wordt het vooral experimenteren. Als het een beetje wil werken plaats ik de basisfuncties in stdavk.h / stdavk.c


Eerste poging: mislukt. Direct schrijven naar het scherm geeft vooral fouten. Laatste poging op GitHub gezet, voor wie er mee verder proberen.

Mijn volgende poging wordt toepassing van de ncurses.h bibliotheek, waarmee je in de termianl zou moeten kunnen tekenen. Eens zien of ik daar blij van word

