#include <stdio.h>

void plus_fout(int var)
{
	var=var+1;
}

void plus_goed(int *var)
{
	*var=*var+1;
}

int main()
{
	int a=10;
	plus_fout(a);
	printf("De waarde van a na plus_fout is %d\n", a);
	plus_goed(&a);
	printf("De waarde van a na plus_goed is %d\n", a);
	
	return 0;
}