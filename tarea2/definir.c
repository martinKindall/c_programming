#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 100
#define KEY_WIDTH 20
#define INDEX_WIDTH 10

void read_line(FILE *file, char *line, int i) {
  if (fseek(file, i*LINE_WIDTH, SEEK_SET)!=0) {
    perror("compare_file_lines");
    exit(1);
  }
  if (fread(line, 1, LINE_WIDTH, file)!=LINE_WIDTH) {
    perror("compare_file_lines");
    exit(1);
  }
}

void trimwhitespace(char *str)
{
	char *p = strchr(str, ' ');
	if (!p)
	{
		return;
	}
	*p = 0;
}

void definirKeyABB(FILE *file, int linea, char *key)
{
	int nodo;
	char busqueda[LINE_WIDTH];
	char* pBusqueda = busqueda;

    read_line(file, busqueda, linea);

    char searchKey[KEY_WIDTH];
    strncpy(searchKey, pBusqueda + 2*INDEX_WIDTH, KEY_WIDTH);
    trimwhitespace(searchKey);

    char leftNode[INDEX_WIDTH];
    strncpy(leftNode, pBusqueda, INDEX_WIDTH);

    char rightNode[INDEX_WIDTH];
    strncpy(rightNode, pBusqueda + INDEX_WIDTH, INDEX_WIDTH);

    int cmp = strcmp(searchKey, key);

    if (cmp == 0)
    {
    	printf("redefinir\n");
    }
    else if(cmp > 0){
    	printf("es mayor\n");
    	nodo = atoi(leftNode);
    	printf("El nodo es: %d\n", nodo);
    }
    else
    {
    	printf("es menor\n");
    	nodo = atoi(rightNode);
    	printf("El nodo es: %d\n", nodo);
    }

    printf("Raiz: %s\n", searchKey);
}

int main(int argc, char **argv) {
	if (argc!=4) {
		fprintf(stderr, "uso: %s <archivo> <llave> <definicion>\n", argv[0]);
		exit(1);
	}

	char *filename= argv[1];
	char *key= argv[2];
	char *value= argv[3];

	FILE *file= fopen(filename, "r+");

	definirKeyABB(file, 0, key);
}