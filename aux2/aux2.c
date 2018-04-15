#include <stdio.h>
#include <string.h>

int palindrome(char *s)
{	
	int largo = strlen(s);
	char aux[largo+1];
	aux[largo] = 0;   // terminacion

	for (int i = 0; i < largo; ++i)
	{
		aux[largo-i-1] = s[i];
	}

	return !strcmp(s, aux);
}

int main()
{
	char p1[] = "reconocer";
	char p2[] = "casas";
	char p3[] = "aboba";

	printf("Es palindrome? %d\n", palindrome(p1));
	printf("Es palindrome? %d\n", palindrome(p2));
	printf("Es palindrome? %d\n", palindrome(p3));

	return 0;
}