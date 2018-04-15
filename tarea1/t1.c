#include <stdio.h>
#include <string.h>
#include "t1.h"

// int main()
// {
// 	uint res = recortar(0b011010101111010100101100, 19, 8);
// 	// uint res = recortar(0xffffffff, 0, 0);

// 	uint testRes = 0b011000101100;
// 	if (res == testRes)
// 	{
// 		printf("paso test\n");
// 	}

// 	char *str1 = "holanda ";
// 	char strAux[strlen(str1) + 1];
// 	strcpy(strAux, str1);
// 	printf("%s\n", strAux);
// 	shiftStringRight(strAux);
// 	printf("%s\n", strAux);
// 	shiftStringRight(strAux);
// 	printf("%s\n", strAux);
// 	shiftStringRight(strAux);
// 	printf("%s\n", strAux);
// }

// int main()
// {
// 	char test1[]= "mhello   \0f";
// 	alinear_der(test1);
// }

uint recortar(uint x, int i, int j)
{
	uint auxL = (x >> i) >> 1;

	uint maskR = (1 << j) - 1;
	uint auxR = x & maskR;
	return (auxL << j) | auxR;
}

void shiftStringRight(char *str)
{
	int largo = strlen(str);
	char *origin = str;
	char aux[strlen(str)+1];
	char *auxP = aux;
	*auxP++ = ' ';

	for (int i = 0; i < largo-1; ++i)
	{
		*auxP = *str;
		++auxP;
		++str;
	}
	*auxP = 0;

	strcpy(origin, aux);
}

void alinear_der(char *str){
	int largo = strlen(str);
	char auxCopy[strlen(str) + 1];
	strcpy(auxCopy, str);

	char *cola = auxCopy + largo - 1;

	while(largo && (*cola == ' '))
	{
		shiftStringRight(str);
		--cola;
		--largo;
	}
}

