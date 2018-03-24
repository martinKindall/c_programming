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

// no funciona en negativos
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

int bits1_neg(int n)
{
	int count = 0;

	for (int mask = 1; mask; mask<<=1)
	{
		if (mask & n) ++count;
	}

	return count;
}

unsigned char rotate(unsigned char c, int bits)
{
	unsigned char clone = c;
	unsigned char aux;

	if (bits > 0)
	{
		clone >>= bits;
		aux = 0xFF >> (8 - bits);

		if (c & aux) clone |= ((c & aux) << (8 - bits));  // mete un 1 a la izquierda si habia un 1 en el LSB
	}
	else if (bits < 0)
	{
		bits *= -1;
		clone <<= bits;
		aux = 0xFF << (8 - bits);

		if (c & aux) clone |= ((c & aux) >> (8 - bits));  // mete un 1 a la derecha si es que habia un 1 en el MSB
	}

	return clone;
}

int main()
{
	int num = 0;
	printf("tamaño %lu bytes\n", sizeof(num));
	printf("tamaño custom %d bits\n", sizeOfInt());

	int num2 = 5;
	int num3 = -1;
	printf("nro %d tiene %d bits en 1\n", num2, bits1(num2));
	printf("nro %d tiene %d bits en 1\n", num3, bits1_neg(num3));

	unsigned char test = 0x09;
	printf("antes de rotar a la derecha %u, despues %u\n", test, rotate(test, 3));
	printf("antes de rotar a la izquierda %u, despues %u\n", test, rotate(test, -3));
	
	return 0;
}
