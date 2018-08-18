// cliente

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#include "jsocket.h"
#include "util.h"

int main(int argc, char** argv)
{
	if (argc > 4 || argc < 1)
	{
		printf("Error de uso\n");
		printf("./cartero r\n");
		printf("./cartero e <prioridad> <mensaje>\n");
		exit(1);
	}

	char modo = *argv[1];

	int s = j_socket();

	if (j_connect(s, "localhost", 3000) < 0)
	{
		printf("Error de conexion\n");
		exit(1);
	}

	if (modo == 'r')
	{
		sendstr(s, "holanda");
	}
	else if (modo == 'e')
	{
		int prioridad = atoi(argv[2]);
		char* mensaje = argv[3];
	}

	return 0;
}