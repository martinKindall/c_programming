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

int posicionBits(int x, int p, int n)
{
	int mask = (1 << n) - 1;

	for (int i = 0; i < (32 - n + 1); ++i)
	{
		int aux = mask & x;
		if (!(aux ^ p)) return i;
		p <<= 1;
		mask <<= 1;
	}

	return -1;
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

	unsigned char test = 0xF0;
	printf("antes de rotar a la derecha %u, despues %u\n", test, rotate(test, 4));
	printf("antes de rotar a la izquierda %u, despues %u\n", test, rotate(test, -3));
	
	int num4 = 0xC00;
	int patron = 0x3;
	int size = 2;

	printf("El numero %d tiene el patron %d en la posicion %d\n", num4, patron, posicionBits(num4, patron, size));

	return 0;
}
