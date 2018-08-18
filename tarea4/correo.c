// servidor 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#include "jsocket.h"
#include "casilla.h"
#include "util.h"

typedef void *(*Thread_fun)(void *);

Casilla cas;


void* serv(void* p) 
{
	intptr_t s = (intptr_t) p;

	char modo;
	read(s, &modo, 1);

	if (modo == 'r')
	{
		char* msg = recibir(cas);
		sendstr(s, msg);
		free(msg);
	}
	else
	{
		char* prior = getstr(s);
		int prioridad = atoi(prior);
		char* mensaje = getstr(s);

		enviar(cas, mensaje, prioridad);

		char close = '1';
		write(s, &close, 1);

		free(prior);
		free(mensaje);
	}

	return NULL;
}


int main(int argc, char** argv)
{
	cas = nuevaCasilla();

	if (argc != 2)
	{
		printf("error de uso.\n");
		printf("./correo <port>\n");
		exit(1);
	}

	int port = atoi(argv[1]);

	int s = j_socket();

	if (j_bind(s, port) < 0)
	{
		printf("error de conexion al puerto\n");
		exit(1);
	}

	while(1)
	{
		intptr_t s2 = j_accept(s);

		pthread_t pid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
		{
			printf("No se pudo establecer atributo\n");
		}

		if (pthread_create(&pid, &attr, (Thread_fun)serv, (void *)s2) != 0) 
		{
	    	printf("No pude crear thread para nuevo cliente");
			close(s2);
	    }
	    pthread_attr_destroy(&attr);
	}

	return 0;
}


