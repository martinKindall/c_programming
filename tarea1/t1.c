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
// }

uint recortar(uint x, int i, int j)
{
	uint auxL = (x >> i) >> 1;

	uint maskR = (1 << j) - 1;
	uint auxR = x & maskR;
	return (auxL << j) | auxR;
}

void alinear_der(char *str){

}