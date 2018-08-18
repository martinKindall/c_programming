// cliente

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "jsocket.h"
#include "util.h"


void mostrarUso()
{
	printf("Error de uso\n");
	printf("./cartero r\n");
	printf("./cartero e <prioridad> <mensaje>\n");
	exit(1);
}


void segFault()
{
	printf("Debe exportar la variable de entorno con la informacion del servidor\n");
	printf("CORREO=servidor.com:3000\n");
	printf("Si el problema persiste contactarse con el desarrollador.\n");
	exit(1);
}

int main(int argc, char** argv)
{
	if (argc > 4 || argc < 1)
	{
		mostrarUso();
	}

	signal(SIGSEGV, segFault);

	char* var_correo = getenv("CORREO");

	char* split = strtok(var_correo, ":");
	char* dominio = split;
	split = strtok(NULL, ":");
	int port = atoi(split);

	int s = j_socket();

	if (j_connect(s, dominio, port) < 0)
	{
		printf("Error de conexion\n");
		exit(1);
	}

	char modo = *argv[1];

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