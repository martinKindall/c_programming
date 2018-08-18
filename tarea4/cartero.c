// cliente

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#include "jsocket.h"
#include "util.h"


void mostrarUso()
{
	printf("Error de uso\n");
	printf("./cartero r\n");
	printf("./cartero e <prioridad> <mensaje>\n");
	exit(1);
}

int main(int argc, char** argv)
{
	if (argc > 4 || argc < 1)
	{
		mostrarUso();
	}

	char modo = *argv[1];

	int s = j_socket();

	if (j_connect(s, "localhost", 3000) < 0)
	{
		printf("Error de conexion\n");
		exit(1);
	}

	write(s, &modo, 1);

	if (modo == 'r')
	{
		char* msj = getstr(s);
		printf("%s\n", msj);
		free(msj);

		return 0;
	}

	else if (modo == 'e')
	{
		char* prioridad = argv[2];
		char* mensaje = argv[3];

		sendstr(s, prioridad);
		sendstr(s, mensaje);

		char resp;
		leer(s, &resp, 1);
	}
	else
	{
		mostrarUso();
	}

	return 0;
}