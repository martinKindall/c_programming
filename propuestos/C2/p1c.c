#include <stdio.h>
#include <pthread.h>
#include "integral.h"
#include <stdlib.h>

/* Programe aca la funcion integral_g_dx_dy_par */

typedef struct params{
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
	*(params->res) = *(params->res) + resAux;
	pthread_mutex_unlock(params->mutex);	

	return NULL;
}

double integral_g_dx_dy_par(double xi, double xf, int n,
                            double yi, double yf, int m)
{
	int cores = 2;
	pthread_t hilos[cores];
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	double resultado;

	for (int i = 0; i < cores; ++i)
	{
		Param parametros = {xi, xf, yi + (yf - yi)/cores * (i), yi + (yf - yi)/cores * (i+1), n, m/cores, &resultado, &mutex};
		pthread_create(&hilos[i], NULL, fun_par, (void*) &parametros);
	}

	for (int i = 0; i < cores; ++i)
	{
		pthread_join(hilos[i], NULL);
	}

	return resultado;
}
