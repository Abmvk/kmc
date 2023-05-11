Als je de debugger gdb wil gebruiken eerst controleren of deze al op je systeem aanwezig is. Pi OS heeft deze standaard, maar als je een ander
systeem gebruikt moet je mogelijk nog installeren. 

Om gdb te kunnen gebruiken moet je je broncode eerst compileren met -g in gcc. Als je mijn Makefile gebruikt zet dan achter de -Wall nog een -g en 
alles werkt zoals bedoeld.

Vervolgens start je gdb op met

gdb programmanaam

of, als je meer informatie wil zien met

gdb -tui programmanaam.

Deze tui-optie geeft je zicht op je source, eventueel de onderliggende assembly als je wil, terwijl de code loopt. Werkt niet altjd goed samen
met bijvoorbeeld een cls() functie, maar dan nog goed voor inzicht.

