#include <stdio.h>
#include <pthread.h>
#include "integral.h"
#include <stdlib.h>

/* Programe aca la funcion integral_g_dx_dy_par */

typedef struct params{
  double xi, xf, yi, yf;
  int n, m;
  double res;
} Param;

void* fun_par(void *ptr)
{
	Param* params = (Param*) ptr;
	double resAux = integral_g_dx_dy(params->xi, params->xf, params->n, params->yi, params->yf, params->m);
	
	params->res = resAux;

	return NULL;
}

double integral_g_dx_dy_par(double xi, double xf, int n,
                            double yi, double yf, int m)
{
	int cores = 8;
	pthread_t hilos[cores];
	double resultado = 0;
	Param parametros[cores];
	double invCores = 1.0/cores;
	double newM = 1.0 * m / cores;

	double auxYi = yi;

	for (int i = 0; i < cores; ++i)
	{
		double auxYf = auxYi + invCores*(yf - yi);
		parametros[i].xi = xi;
		parametros[i].xf = xf;
		parametros[i].yi = auxYi;
		parametros[i].yf = auxYf;
		parametros[i].n = n;
		parametros[i].m = newM;
		auxYi = auxYf;

		pthread_create(&hilos[i], NULL, fun_par, (void*) &parametros[i]);
	}

	for (int i = 0; i < cores; ++i)
	{
		pthread_join(hilos[i], NULL);
	}

	for (int i = 0; i < cores; ++i)
	{
		resultado += parametros[i].res;
	}

	return resultado;
}
