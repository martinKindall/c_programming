#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "colapri.h"
#include "colapri-arreglo.h"

#include <pthread.h>

#include "casilla.h"


typedef struct mensaje {
	void *msg;
	int pri;
} Mensaje;

int compPriorMsg(void *p, void *q) {
	Mensaje* men1 = (Mensaje*)p;
	Mensaje* men2 = (Mensaje*)q;

	return men1->pri - men2->pri;
}

struct casilla {
	ColaPri cola;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

Casilla nuevaCasilla(){
	Casilla casilla = malloc(sizeof(casilla));
	casilla->cola = nuevaColaPriArreglo(100, compPriorMsg);
	pthread_mutex_init(&(casilla->mutex), NULL);

	return casilla;
}


void enviar(Casilla c, void *msg, int pri){
	return;
}

void *recibir(Casilla c){
	return NULL;
}

void destruirCasilla(Casilla c){

}
