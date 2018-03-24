#include <stdio.h>

/**
 * [sizeOfInt: no sabemos el tamaño de un int, pero sabemos que si le asignamos el valor -1 entonces tendremos un 
 * numero binario con todas sus posiciones en 1, luego contamos cada desplazamiento a la izquierda en 8 (1 byte) hazta que el numero sea cero]
 * @return [description]
 */
int sizeOfInt()
{
	int i = -1;
	int size = 0;
	int bits_in_byte = 8;

	while(i)
	{
		size += 1;
		i <<= bits_in_byte;
	}

	return size * bits_in_byte;
}

int bits1(int n)
{
	int bits1 = 0;
	int mask1 = 0x0001;

	while(n)
	{
		if (n & mask1) ++bits1;
		n >>= 1;
	}

	return bits1;
}


int main()
{
	int num = 0;
	printf("tamaño %lu bytes\n", sizeof(num));
	printf("tamaño custom %d bits\n", sizeOfInt());

	int num2 = 0xFF;
	printf("nro %d tiene %d bits en 1\n", num2, bits1(num2));
	
	return 0;
}
