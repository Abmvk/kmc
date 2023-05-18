Voor extra gemak een paar aanpassingen gedaan:

1. Een directory ~/bin gemaakt. Pi OS zet die automatisch vooraan in het PATH, en dat betekent dat ieder programma dat je in ~/bin plaatst
kan worden gebruikt zonder ./ er voor.

2. Op GitHub een repo gemaakt "bin", die een kopie is van ~/bin op iedere Pi die ik gebruik, zodat die synchroon blijven

3. De Makefile, stdavk.c, stdavk.h, tenplate.c en writec die ik tot nu toe steeds moest meekopieren naar een nieuwe directory, in ~/bin gezet

4. In ~/bin een bash-script gemaakt met de naam getmake, waarmee de Makefile en de stdavk.* gekopieerd worden uit ~/bin naar de huidige directory


Dat levert op dat een nieuw programma geschreven kan worden met

writec nieuw.c

en vervolgens gecompileerd met twee stappen:

getmake
make src=nieuw.c exe=nieuw

Van belang is nu natuurlijk wel dat alle aanpassingen in de Makefile of in de stdavk-lib (of welke naam je zelf ook wil gebruiken), of in de
template.c wel in ~/bin worden gemaakt en niet ergens anders.

