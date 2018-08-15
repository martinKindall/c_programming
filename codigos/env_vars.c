#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* p;

	p = getenv("HOME");

	printf("%s\n", p);

	return 0;
}