#include "integral.h"

double integral(Funcion f, void *p, double xi, double xf, int n)
{
	double h = (xf - xi)/n;

	double primerTermino = (f(p, xi) + f(p, xf)) / 2.0;

	double segundoTermino = 0;

	for (int i = 0; i < n; ++i)
	{
		segundoTermino += f(p, xi + i*h);
	}

	return h * (primerTermino + segundoTermino);
}