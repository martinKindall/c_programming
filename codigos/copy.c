#include <stdio.h>
 
/* 
 * Copia la entrada en su salida sin modificaciones
 */
 
int main() 
{
	int c;

	putchar(53);
	putchar(053);
	putchar(0x3a);

	char d = 0;
	putchar(d);
 
 	// EOF corresponde a ctrl+d
    while(c != EOF)
    {
        c = getchar();
        putchar(c);
    }
 
	printf("\n");
	printf("cerrando\n");

    return 1;
}
