#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 100

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
	*p = 0;
}

int main(int argc, char **argv) {
	if (argc!=4) {
		fprintf(stderr, "uso: %s <archivo> <llave> <definicion>\n", argv[0]);
		exit(1);
	}

	char *filename= argv[1];
	char *key= argv[2];
	char *value= argv[3];

	printf("%s\n", filename);
	printf("%s\n", key);
	printf("%s\n", value);

	FILE *file= fopen(filename, "r+");

	char busqueda[LINE_WIDTH];
	char* pBusqueda = busqueda;

    read_line(file, busqueda, 0);

    char searchKey[20];
    strncpy(searchKey, pBusqueda + 20, 20);
    trimwhitespace(searchKey);

    printf("%s\n", busqueda);
    printf("%s\n", searchKey);
}