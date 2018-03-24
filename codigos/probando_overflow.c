#include <stdio.h>
 
int main() 
{
	char c1 = 127; 
	char c2 = 1;
	char resC = c1 + c2;
	int res = c1 + c2;

	printf("El resultado char es %c\n", resC);
	// overflow, imprime lo mismo que -128
	printf("El resultado int es %d\n", res);
	// 128, no hay problema

	return 0;	
}