#include <stdio.h>
 
/* 
 * Copia la entrada en su salida sin modificaciones
 */
 
int main() 
{
	int c;
 
    while((c=getchar()) != EOF)
        putchar(c);
 
    return 1;
}
