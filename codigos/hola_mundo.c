#include <stdio.h>

int main(){
	printf("Hola Mundo!\n");

	for (int i = 0; i < 10; ++i)
	{
		printf("%d\n", i);
	}

	printf("\n%d\n", sizeof(int));

	int num = -2147483648;
	printf("El numero %d se multiplica por 2 usando shifts y se obtiene: %d\n", num, num<<3);

	char *nombre_fruta[]= { "manzana", "pera", "guinda", "durazno", "damasco" };

	for (int i = 0; i < 5; ++i)
	{
		printf("%s\n", nombre_fruta[i]);
	}

	unsigned int x = 4;
	unsigned y = 10;
	printf("%d\n", sizeof(unsigned));
	printf("%d\n", x+y);

	printf("%d\n", 0b001011);
	printf("%d\n", 0xA0);

	return 0;
}