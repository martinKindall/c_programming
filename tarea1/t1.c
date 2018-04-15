#include <stdio.h>
#include <string.h>
#include "t1.h"

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

