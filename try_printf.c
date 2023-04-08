#include <stdio.h>


int main()
{
	int ch;

	for(ch=65;ch<=67;ch++)
	{
		printf("ASCII %d = %c\n", ch, ch);	// %d voor decimale weergave, %c geeft een character en \n een nieuwe regel
	}

	for(;ch<=69;ch++) 				// geen startwaarde voor ch, dus ch gaat gewoon verder waar het gebleven was
	{
		printf("\tASCII %d = %c\n", ch, ch);	// als extra nu een \t wat staat voor tab
	}

	for(float x = 2; x<4 ;x++)
	{
		printf("1/%e = %E\n", x, 1/x);		// %e en %E geven een wetenschappelijke notatie van a*10^b, met de e of E voor 10^
		printf("1/%f = %f\n", x, 1/x);		// %f geeft een gewone decimaal
		printf("1/%G = %G\n", x, 1/x);		// %G kiest de kortste weergave, met of zonder e
		printf("1/%d = %d\n\n", x, 1/x);	// een float proberen weer te geven als int KAN wel, maar het resultaat klopt niet
	}


	printf("\n\ndec\toct\thex\tHEX\n");
	for(char y=4;y<17;y++)
	{
		printf("%u\t%o\t%x\t%X\n",y ,y ,y ,y);	// dezelfde waarde decimaal, octaal, hexadecimaal in klein en groot
	}

	printf("\nPointer naar ch = %p\n", &ch);	// %p geeft een pointer, & voor de x geeft de pointer naar x
	printf("Pointer naar ch? = %p\n", ch);		// zonder de & is het geen pointer!
	printf("Nee, gewoon de waarde in hex: ch = %X\n\n", ch);

	return 0;
}

