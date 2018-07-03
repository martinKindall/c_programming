#include "integral.h"

/* estas funciones aparecen en el enunciado y las necesitara */

typedef struct params
{
	double xi, xf;
	int n;
} Params;

double g_aux(void *ptr, double x) 
{
	double y= *(double *)ptr;
	return g(x, y);
}

double integral_g_dx(double xi, double xf, double y, int n) {
	return integral(g_aux, &y, xi, xf, n);
}

double func_aux(void* ptr, double y)
{
	Params* params = (Params*) ptr;
	return integral_g_dx(params->xi, params->xf, y, params->n);
}

double integral_g_dx_dy(double xi, double xf, int n, double yi, double yf, int m)
{
	Params parametros = {xi, xf, n};

	return integral(func_aux, (void*)&parametros, yi, yf, m);
}

/* Programe aca la funcion integral_g_dx_dy.
 *
 * Hint:
 * integral en [yi,yf] integral en [xi, xf] g(x,y) dx y  se aproxima a
 *                  integral en [yi,yf]  integral_g_dx(xi, xf, y, n) dx
 *
 * Defina una funcion auxiliar con un encabezado compatible para usarla
 * como parametro de la funcion integral:
 *
 * double integral_g_dx_aux(void *ptr, double y) {
 *   ... calcule aca integral_g_dx(xi, xf, y, n) dx llamando a integral ...
 * }
 *
 * Tambien debe invocar integral en la funcion integral_g_dx_dy:
 *
 * double integral_g_dx_aux( ... ) {
 *   ... integral(integral_g_dx_aux, ...);
 * }
 *
 * El truco esta en pasar en ptr una estructura Param con los parametros
 * xi, xf y n que se necesitan en integral_g_dx_aux.
 */



