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

	/* ------  */

	int a = 2147483647;
	double x = a + 1;
	printf("El resultado double es %f\n", x);
	// overflow, -2147483648.000000
	
	int b = 2147483647;
	double y = b + 1.0;  // aca realiza una suma double, se elimina el problema
	printf("El resultado double es %f\n", y);
	// 2147483648.000000

	return 0;	
}