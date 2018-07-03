#include <stdio.h>
#include <pthread.h>
#include "integral.h"
#include <stdlib.h>

/* Programe aca la funcion integral_g_dx_dy_par */

typedef struct {
  double xi, xf, yi, yf;
  int n, m;
  double* res;
  pthread_mutex_t* mutex;
} Param;

void* fun_par(void *ptr)
{
	Param* params = (Param*) ptr;
	double resAux = integral_g_dx_dy(params->xi, params->xf, params->n, params->yi, params->yf, params->m);
	
	pthread_mutex_lock(params->mutex);	
	*(params->res) += resAux;
	pthread_mutex_unlock(params->mutex);	

	return NULL;
}

double integral_g_dx_dy_par(double xi, double xf, int n,
                            double yi, double yf, int m)
{
	int cores = 8;
	pthread_t hilos[cores];
	pthread_mutex_t mutex;
	double resultado = 0;

	Param* parametros = malloc(sizeof(Param));
	parametros->xi = xi;
	parametros->xf = xf;
	parametros->n = n;
	parametros->mutex = &mutex;
	parametros->res = &resultado;

	for (int i = 0; i < cores; ++i)
	{
		parametros->yi = yi/cores * (i);
		parametros->yf = yi/cores * (i+1);
		parametros->m = m/cores;
		pthread_create(&hilos[i], NULL, fun_par, (void*) parametros);
	}

	for (int i = 0; i < cores; ++i)
	{
		pthread_join(hilos[i], NULL);
	}

	return resultado;
}
