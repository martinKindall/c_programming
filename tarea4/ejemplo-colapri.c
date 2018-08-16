#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "colapri.h"
#include "colapri-arreglo.h"

// Entre 2 strings la mayor prioridad lo tiene el que aparece antes
// en un diccionario (orden lexicografico).
int compri_strings(void *p, void *q) {
  return strcmp(p, q);
}

int main() {
  ColaPri c= nuevaColaPriArreglo(100, compri_strings);
  c->ops->agregar(c, "pedro");
  c->ops->agregar(c, "juan");
  c->ops->agregar(c, "diego");
  char *s= c->ops->mejor(c);
  printf("El mejor es %s\n\n", s);

  printf("Prueba del iterador\n");
  IterColaP iter= c->ops->iterador(c);
  while (iter->ops->continua(iter)) {
    s= iter->ops->proximo(iter);
    printf("%s\n", s);
  }
  iter->ops->destruir(iter);

  printf("\nExtraccion de todos los elementos de la cola\n");
  while (c->ops->tamano(c)!=0) {
    s= c->ops->extraer(c);
    printf("%s\n", s);
  }
  c->ops->destruir(c);
  return 0;
}
