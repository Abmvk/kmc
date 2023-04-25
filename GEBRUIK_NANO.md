nano is een vrij simpele, handige teksteditor. Voor een tekst als deze gebruik je simpelweg

$ nano GEBRUIK_NANO.md

Maar je kan met nano bijne hetzelfde bereiken als met code editors zoals Runestone op de iPad, of Geanny in de GUI van PI OS. Nano kent een hele
reeks opties, waarvan ik er drie handig vind:

-i zorgt dat nano blijft inspringen. Dus als je code bestaat uit:

{
	hier_iets();
	hier_nog_iets();
}

dan hoef je niet beide keren een tab te geven, nano vult die na de eerste keer zelf in. Lijkt niet spannend, maar bij veel code wordt het wel 
nuttig.

-l zorgt dat nano regelnummers toevoegt. Dat is alleen al handig om foutmeldingen van de compiler snel terug te kunnen vinden, want gcc geeft
ook het regelnummer waar iets is mis gegaan.

-Y c tenslotte geeft nano ahw kennis van C, zodat woorden een kleur krijgen op basis van wat nano herkent. Dit komt de leesbaarheid van je code
enorm ten goede.

Dan mis je nog steeds functies die "echte" code-editors hebben, zoals het automatisch plaatsen van sluit haken, ), } en ], autocompletion, etc.,
maar het is toch echt een goed begin. Je kan de opties combineren, dus dan krijgt je zoiets als

$ nano -ilY c test.c

Let er op dat in Linux hoofdletters en kleine letters NIET hetzelfde zijn. Ook niet bij de opties van nano.

 
