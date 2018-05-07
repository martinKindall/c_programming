#include <stdio.h>

typedef struct punto{
	float x,y;
}Punto;

int devuelve(int a[]){
	return a[0];
}

int main(){
	Punto pa = {0,10};
	Punto pb;

	Punto* pc = &pa;

	printf("La coordenada x es %f\n", pa.x);
	printf("La coordenada x es %f\n", pc->x);

	int numeros[] = {1,2,3,4};
	int* arrNum = malloc(sizeof(int)*2);
	arrNum[0] = 1;
	arrNum[1] = 50;

	printf("%d\n", devuelve(arrNum));
}
