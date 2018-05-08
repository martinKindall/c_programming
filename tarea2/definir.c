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

void insertarString(char *def, char *dest, int size, int terminacion)
{
	strcpy(dest, def);
	int largo = strlen(dest);
	char *ptr = dest + largo;
    if (terminacion)
    {
        size--;
    }
	if (strlen(dest) < size)
	{
		for (int i = 0; i < size - largo; ++i){
			*ptr = ' ';
			++ptr;
		}
	}
    if (terminacion)
    {
        *ptr = '\n';
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
    	insertarString(definicion, reemplazo, DEF_WIDTH, 1);

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

    	char current_index[INDEX_WIDTH];
        insertarString(ultima_lin, current_index, INDEX_WIDTH, 0);

        if (dir)
        {
            strncpy(
            pBusqueda + INDEX_WIDTH,
            current_index,
            INDEX_WIDTH
            );
        }
        else
        {
            strncpy(
            pBusqueda,
            current_index,
            INDEX_WIDTH
            );
        }

        write_line(file, busqueda, linea);

    	insertarString("-1", current_index, INDEX_WIDTH, 0);

    	strncpy(
    		pBusqueda,
    		current_index,
    		INDEX_WIDTH
    		);

    	strncpy(
    		pBusqueda + INDEX_WIDTH,
    		current_index,
    		INDEX_WIDTH
    		);

        char current_def[DEF_WIDTH];
        insertarString(definicion, current_def, DEF_WIDTH, 1);
        strncpy(
            pBusqueda + 2*INDEX_WIDTH + KEY_WIDTH,
            current_def,
            DEF_WIDTH
            );

        char current_key[KEY_WIDTH];
        insertarString(key, current_key, KEY_WIDTH, 0);
        strncpy(
            pBusqueda + 2*INDEX_WIDTH,
            current_key,
            KEY_WIDTH
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