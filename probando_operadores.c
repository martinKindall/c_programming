#include <stdio.h>
 
int main() 
{
	int c = 0x3a;
	putchar(c);
	printf("\n");
	putchar(c << 1);
	printf("  fin\n");

	return 0;
}