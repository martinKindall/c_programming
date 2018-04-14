#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t1.h"

int main() {
  // Test a.1
  // recortar(x, 0, 0)==r1, con x== 'puros unos' y r1== '31 unos'
  uint r1= recortar(0xffffffff, 0, 0);
  if (r1!=0x7fffffff) {
    fprintf(stderr, "test a.1 falla: dio 0x%x en vez de 0x7fffffff\n", r1);
    exit(1);
  }

  // Test a.2
  // recortar(x, 31, 0)==r2, con x== 'puros unos' y r2== 0
  // ¡Cuidado! Recuerde que no puede desplazar x en 32 o mas bits.
  uint r2= recortar(0xffffffff, 31, 0);
  if (r2!=0) {
    fprintf(stderr, "test a.2 falla: dio 0x%x en vez de 0\n", r2);
    exit(1);
  }

  // Test a.3
  // recortar(0b0110 1010 1111 0101 0010 1100, 19, 8)==0b0110 0010 1100)
  // debe borrar          ^^^^ ^^^^
  uint r3= recortar(0x006af52c, 19, 8);
  if (r3!=0x62c) {
    fprintf(stderr, "test a.3 falla: dio 0x%x en vez de 0x62c\n", r3);
    exit(1);
  }

  // Test b.1
  char test1[]= "mhello   \0f"; // El \0 es la terminacion del string
  int l1= strlen(test1);
  // El argumento es test+1 y por lo tanto es el string "hello   "
  alinear_der(test1+1); // el parametro es "hello   ", no se debe modificar la m
  if (strcmp(test1, "m   hello")!=0) {
    fprintf(stderr, "test b.1 falla: %s\n", test1);
    exit(1);
  }
  if (test1[l1+1]!='f') {
    // No se debio haber modificado la f despues de \0
    fprintf(stderr, "test b.1 falla: %c\n", test1[l1+1]);
    exit(1);
  }

  // Test b.2
  char test2[]= "m  ";
  alinear_der(test2+1); // el parametro es "  ", no se debe modificar la m
  if (strcmp(test2, "m  ")!=0) {
    fprintf(stderr, "test b.2 falla: %s\n", test2);
    exit(1);
  }

  char test3[]= "m    hola  que  tal   \0f";
  int l3= strlen(test3);
  alinear_der(test3+1);
  if (strcmp(test3, "m       hola  que  tal")!=0) {
    fprintf(stderr, "test b.3 falla: %s\n", test3);
    exit(1);
  }
  if (test3[l3+1]!='f') {
    // No se debio haber modificado la f despues de \0
    fprintf(stderr, "test b.3 falla: %c\n", test3[l3+1]);
    exit(1);
  }

  printf("Felicitaciones, todos los tests funcionan correctamente\n");
  return 0;
}
