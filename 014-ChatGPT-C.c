#include <stdio.h> 

void tropisch_checker(int temp) 
{ 
	if (temp >= 30) 
	{ 
		printf("Het is een tropische dag, denk eraan dat je genoeg drinkt!"); 
	} 
	else 
	{ 
		printf("Het is geen tropische dag."); 
	} 
} 

int main() 
{ 
	int temperatuur = 29; 
	tropisch_checker(temperatuur); 

return 0; 
}
