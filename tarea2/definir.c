#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_WIDTH 100
#define KEY_WIDTH 20
#define INDEX_WIDTH 10
#define DEF_WIDTH 60

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

void write_line(FILE *file, char *line, int i) {
  if (fseek(file, i*LINE_WIDTH, SEEK_SET)!=0) {
    perror("compare_file_lines");
    exit(1);
  }
  if (fwrite(line, 1, LINE_WIDTH, file)!=LINE_WIDTH) {
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

void insertarDefinicion(char *def, char *dest)
{
	strcpy(dest, def);
	int largo = strlen(dest);

	char *ptr = dest + largo;

	if (strlen(dest) < 59)
	{
		for (int i = 0; i < 59 - largo; ++i){
			*ptr = ' ';
			++ptr;
		}
	}
	*ptr = '\n';
}

void insertarString(char *def, char *dest, int size)
{
	strcpy(dest, def);
	int largo = strlen(dest);

	char *ptr = dest + largo;

	if (strlen(dest) < size)
	{
		for (int i = 0; i < size - largo; ++i){
			*ptr = ' ';
			++ptr;
		}
	}
}

void definirKeyABB(FILE *file, int linea, char *key, char *definicion)
{
	int nodo;
	int dir;
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
    	char reemplazo[DEF_WIDTH];
    	insertarDefinicion(definicion, reemplazo);

    	strncpy(
    		pBusqueda + 2*INDEX_WIDTH + KEY_WIDTH,
    		reemplazo,
    		DEF_WIDTH
    		);

    	write_line(file, busqueda, linea);
    	return;
    }
    else if(cmp > 0){
    	nodo = atoi(leftNode);
    	dir = 0;
    }
    else
    {
    	nodo = atoi(rightNode);
    	dir = 1;
    }

    if (nodo < 0)
    {
    	fseek(file, -LINE_WIDTH, SEEK_END);
    	int ultima_linea = ftell(file)/LINE_WIDTH + 1;
        char ultima_lin[5];
        sprintf(ultima_lin, "%d", ultima_linea);

    	char reemplazo[INDEX_WIDTH];
        insertarString(ultima_lin, reemplazo, INDEX_WIDTH);

        if (dir)
        {
            strncpy(
            pBusqueda + INDEX_WIDTH,
            reemplazo,
            INDEX_WIDTH
            );
        }
        else
        {
            strncpy(
            pBusqueda,
            reemplazo,
            INDEX_WIDTH
            );
        }

        write_line(file, busqueda, linea);

    	insertarString("-1", reemplazo, INDEX_WIDTH);

    	strncpy(
    		pBusqueda,
    		reemplazo,
    		INDEX_WIDTH
    		);

    	strncpy(
    		pBusqueda + INDEX_WIDTH,
    		reemplazo,
    		INDEX_WIDTH
    		);

        char reemplazo_2[DEF_WIDTH];
        insertarDefinicion(definicion, reemplazo_2);
        strncpy(
            pBusqueda + 2*INDEX_WIDTH + KEY_WIDTH,
            reemplazo_2,
            DEF_WIDTH
            );

    	write_line(file, busqueda, ultima_linea);
    	return;
    }
    else
    {
		definirKeyABB(file, nodo, key, definicion);
    }
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

	definirKeyABB(file, 0, key, value);
}