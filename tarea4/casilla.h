
// Implemente la estructura casilla en casilla.c con:
// struct casilla {
//   ... los campos que Ud. requiera como por ejemplo:
//   ... un mutex, una condicion, una cola de prioridades, etc.
// }
// No haga nuevamente el typedef.

typedef struct casilla *Casilla;

// Debe implementar estas funciones en el archivo casilla.c

Casilla nuevaCasilla();
void enviar(Casilla c, void *msg, int pri);
void *recibir(Casilla c);
void destruirCasilla(Casilla c);

// Esta funcion esta implementada en el archivo test-casilla.c

void error(char *fmt, ...);

