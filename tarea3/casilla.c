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
	pthread_cond_t cond_rec;
} Mensaje;

int compPriorMsg(void *p, void *q) {
	Mensaje* men1 = (Mensaje*)p;
	Mensaje* men2 = (Mensaje*)q;

	return men2->pri - men1->pri;
}

struct casilla {
	ColaPri cola;
	pthread_mutex_t mutex;
	pthread_cond_t cond_env;
};

Casilla nuevaCasilla(){
	Casilla casilla = malloc(sizeof(struct casilla));
	casilla->cola = nuevaColaPriArreglo(100, compPriorMsg);
	pthread_mutex_init(&(casilla->mutex), NULL);
	pthread_cond_init(&(casilla->cond_env), NULL);

	return casilla;
}

void enviar(Casilla c, void *msg, int pri){
	pthread_mutex_lock(&c->mutex);
	Mensaje *final_msg = malloc(sizeof(struct mensaje));
	final_msg->msg = msg;
	final_msg->pri = pri;
	pthread_cond_init(&(final_msg->cond_rec), NULL);

	c->cola->ops->agregar(c->cola, (void*)final_msg);
	pthread_cond_broadcast(&c->cond_env);

	pthread_cond_wait(&(final_msg->cond_rec), &c->mutex);
	free(final_msg);
	pthread_mutex_unlock(&c->mutex);
}

// void enviar_alternativa(Casilla c, void *msg, int pri){
// 	pthread_mutex_lock(&c->mutex);
// 	Mensaje final_msg = {msg, pri};
// 	pthread_cond_init(&(final_msg.cond_rec), NULL);

// 	c->cola->ops->agregar(c->cola, (void*)&final_msg);
// 	pthread_cond_broadcast(&c->cond_env);

// 	pthread_cond_wait(&(final_msg.cond_rec), &c->mutex);
// 	pthread_mutex_unlock(&c->mutex);
// }

void *recibir(Casilla c){
	pthread_mutex_lock(&c->mutex);
	while(c->cola->ops->tamano(c->cola) <= 0)
		pthread_cond_wait(&c->cond_env, &c->mutex);

	Mensaje* objPrioritario = (Mensaje*)c->cola->ops->extraer(c->cola);
	void* message = objPrioritario->msg;
	pthread_cond_broadcast(&(objPrioritario->cond_rec));
	pthread_mutex_unlock(&c->mutex);

	return message;
}

void destruirCasilla(Casilla c){
	ColaPri auxCola = c->cola;
	Mensaje* auxMsg;
	while (auxCola->ops->tamano(auxCola)!=0) {
		auxMsg = auxCola->ops->extraer(auxCola);
		free(auxMsg);
	}
	auxCola->ops->destruir(auxCola);
	free(c);
}
