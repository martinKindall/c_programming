#include <stdio.h>

typedef unsigned int uint;

uint recortar(uint x, int i, int j)
{
	int auxL = x >> (i + 1);
	int auxR = x << (32 - j);
	return (auxL << j) | (auxR >> (32 - j));
}

int main()
{
	uint res = recortar(0b011010101111010100101100, 19, 8);
	uint testRes = 0b011000101100;
	if (res == testRes)
	{
		printf("paso test\n");
	}
}