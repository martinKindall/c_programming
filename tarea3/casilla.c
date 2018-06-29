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

	return men2->pri - men1->pri;
}

struct casilla {
	ColaPri cola;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

Casilla nuevaCasilla(){
	Casilla casilla = malloc(sizeof(struct casilla));
	casilla->cola = nuevaColaPriArreglo(100, compPriorMsg);
	pthread_mutex_init(&(casilla->mutex), NULL);

	return casilla;
}

void enviar(Casilla c, void *msg, int pri){
	pthread_mutex_lock(&c->mutex);
	Mensaje *final_msg = malloc(sizeof(struct mensaje));
	final_msg->msg = msg;
	final_msg->pri = pri;

	c->cola->ops->agregar(c->cola, (void*)final_msg);
	pthread_cond_broadcast(&c->cond);

	pthread_cond_wait(&c->cond, &c->mutex);
	pthread_mutex_unlock(&c->mutex);
}

void *recibir(Casilla c){
	pthread_mutex_lock(&c->mutex);
	while(c->cola->ops->tamano(c->cola) == 0)
		pthread_cond_wait(&c->cond, &c->mutex);

	Mensaje* objPrioritario = (Mensaje*)c->cola->ops->extraer(c->cola);
	void* message = objPrioritario->msg;
	free(objPrioritario);
	pthread_cond_broadcast(&c->cond);
	pthread_mutex_unlock(&c->mutex);

	return message;
}

void destruirCasilla(Casilla c){
	pthread_mutex_lock(&c->mutex);
	ColaPri auxCola = c->cola;

	while (auxCola->ops->tamano(auxCola)!=0) {
		auxCola->ops->extraer(auxCola);
	}
	auxCola->ops->destruir(auxCola);

	free(c);
	pthread_mutex_unlock(&c->mutex);
}
