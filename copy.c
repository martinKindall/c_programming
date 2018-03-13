#include <stdio.h>
 
/* 
 * Copia la entrada en su salida sin modificaciones
 */
 
int main() 
{
	int c;
 
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
