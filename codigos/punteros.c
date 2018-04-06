#include <stdio.h>

int main()
{
	int a;

	printf("%d\n", a);
	printf("%p\n", &a);

	int *b = NULL;
	int *c = NULL;

	printf("%p\n", b);

	int size = 3;

	int d[size];

	printf("\nArreglo de ruido\n");

	for (int i = 0; i < size; ++i)
	{
		printf("%d\n", d[i]);
	}
	
	printf("\n\n");

	// d = {2, 2, 2};
	// d = malloc(3*sizeof(int));
	
	int *e = malloc(sizeof(int));
	e[0] = 100;
	printf("%d\n", e[0]);

	*e = 20;   // el contenido en la primera casilla, equivale a e[0]
	printf("%d\n", e[0]);

	// accediendo a una casilla no tomada por este malloc
	printf("%d\n", e[100]);

	e[100] = 3;
	printf("%d\n", e[100]);   // no arroja error, pero esta incorrecto, podriamos estar pisando otras memorias

	char *f = malloc(sizeof(char));
	f[0] = 300;   // char solo tiene tamaño 1 byte, 256 valores
	printf("%c\n", f[0]);   // overflow

	int g[3] = {1, 2, 3};
	printf("%d\n", g[5]); // nos salimos del arreglo, tira cualquier cosa

	int *pointer = NULL;

	printf("%p\n", pointer);   // nil
	printf("%d\n", *pointer);   // segmentation fault (accediendo al contenido de NULL)

	return 0;
}