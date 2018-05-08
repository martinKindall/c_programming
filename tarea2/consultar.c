#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Esta version de consultar es ineficiente porque hace busqueda secuencial.
// Su implementacion de definir debe tomar tiempo O(log n) haciendo la
// insercion correspondiente a un ABB
int main(int argc, char **argv) {
if (argc!=3) {
fprintf(stderr, "uso: %s <archivo> <llave>\n", argv[0]);
exit(1);
}
char *V01= argv[1];
char *V02= argv[2];
FILE *V03= fopen(V01, "r");
char V07[100];
for(;;) {
if (fread(V07, 1, 100, V03)<=0)
break;
char *V05= V07+20;
char *V06= V07+40;
char *V04= V06-1;
while (*V04==' ')
V04--;
V04[1]= 0;
if (strcmp(V02, V05)==0) {
V06[59]= 0;
printf("%s\n", V06);
return 0;
}
}
printf("palabra no encontrada\n");
return 0;
}

