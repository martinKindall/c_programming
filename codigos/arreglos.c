#include <stdio.h>

int strlen(char *s);

int main()
{
	int array[] = {1, 2, 3, 4, 5};

	for (int i = 0; i < 5; ++i)
	{
		printf("%d\n", array[i]);
		printf("%p\n", &array[i]);
	}

	array[4] = 100;
	printf("%d\n", array[4]);

	int *p_to_array = array;

	for (int i = 0; i < 5; ++i)
	{
		printf("%d\n", *(p_to_array+i));
		printf("%d\n", p_to_array[i]);
	}

	printf("Largo del arreglo: %lu\n", sizeof(array)/sizeof(array[0]));

	char s[] = "hola";
	printf("%s\n", s);

	char *r;
	r = s;
	printf("%s\n", r);
	
	s[3] = 'o';
	printf("%s\n", r);
	
	r[1] = 'a';
	printf("%s\n", s);

	char *v = r;
	v[0] = 'H';
	printf("%s\n", s);
	printf("%s\n", r);

	char r2[]= {'h', 'o', 'l', 'a', 0};
	r2[0] = 'H';
	printf("%s\n", r2);

	char *s2 = "hello!";
	printf("%s\n", s2);
	// s2[0] = 'H';  // segmentation fault.
	char s3[] = {'h', 'e', 'l', 'l', 'o', 0};
	printf("%s\n", s3);
	s2 = s3;
	s2[0] = 'H';  //sí funciona
	printf("%s\n", s3);

	printf("%d\n", strlen("hello!"));

	return 0;
}

int strlen(char *s)
{
	char *aux = s;

	while(*aux) ++aux;

	return aux - s;
}