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

void reverse(char *s)
{
	int largo = strlen(s);
	char aux[largo+1];
	strcpy(aux, s);

	for (int i = 0; i < largo; ++i)
	{
		s[i] = aux[largo-i-1];
	}
}

void reverse_2(char *s)
{
	char *i = s;
	char *j = s + strlen(s) - 1;
	char aux;

	while(i < j){
		aux = *i;
		*i = *j;
		*j = aux;

		i++;
		j--;
	}
}

int myStrcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2) {
		s1++;
		s2++;
	}

	return *s1 - *s2;
}

int palindrome2(char *s)
{
	char aux[strlen(s) + 1];
	strcpy(aux, s);
	reverse(aux);

	return !myStrcmp(aux, s);
}

int charNotIn(char *s, char needle)
{
	for (; *s; ++s)
	{
		if (*s == needle) return 0;
	}

	return 1;
}

void eliminar_duplicados(char *str)
{
	char *origin = str;
	char aux[strlen(str)+1];
	char *auxT = aux;
	for (int i = 0; i < strlen(str); ++i)
	{
		*auxT = 0;
		++ auxT;
	}

	aux[strlen(str)] = 0;
	char *auxP = aux;
	int index = 0;

	for (; *str; ++str)
	{
		if(charNotIn(aux, *str))
		{
			*auxP = *str;
			++auxP;
		}
	}
	*auxP = 0;
	strcpy(origin, aux);
}

int main()
{
	char p1[] = "reconocer";
	char p2[] = "casas";
	char p3[] = "aboba";

	printf("Es palindrome? %d\n", palindrome2(p1));
	printf("Es palindrome? %d\n", palindrome2(p2));
	printf("Es palindrome? %d\n", palindrome2(p3));

	char prueba2[] = "albahaca";
	printf("%s\n", prueba2);
	reverse_2(prueba2);
	printf("%s\n", prueba2);

	char *ro= "aabcbddd1b221"; // solo lectura
	char rw[strlen(ro)+1]; // lectura y escritura
	strcpy(rw, ro); // copia el string ro en rw
	eliminar_duplicados(rw); // la funcion pedida
	printf("%s\n", rw); // abcd12

	return 0;
}