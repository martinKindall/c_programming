#include <stdio.h>

typedef struct punto{
	float x,y;
}Punto;


int main(){
	Punto pa = {0,10};
	Punto pb;

	Punto* pc = &pa;

	printf("La coordenada x es %f\n", pa.x);
	printf("La coordenada x es %f\n", pc->x);
}