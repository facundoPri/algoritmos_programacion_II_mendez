/*
 * Diagrame cómo queda el Stack y el Heap al
 * finalizar la ejecución.
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_CAJONES 5
#define MAX_COSAS 50
#define MAX_DESCRIPCION 500

typedef struct cosa {
  char descripcion[MAX_DESCRIPCION];
} cosa_t;

typedef struct cajon {
  int ancho;
  int largo;
  cosa_t *cosas;
  int cantidad_cosas;
} cajon_t;

int main() {
  cajon_t *cajones = malloc(MAX_CAJONES * sizeof(cajon_t));
  for (int i = 0; i < MAX_CAJONES; i++) {
    cajones[i].cosas = malloc(MAX_COSAS * sizeof(cosa_t));
  }

  /* La cosa 35 del 35 cajon es un cargador */
  cajones[35].cosas[35].descripcion = "cargador";
  printf("%d", cajones[35].cosas[35].descripcion);

  /* Como liberamos esa memoria? */
  /* for (int i = 0; i < MAX_CAJONES; i++) { */
  /*   free(cajones[i].cosas); */
  /* } */
  /* free(cajones); */
}

/*
Creamos un puntero cajones de tipo cajon_t, reservamos memoria para 5 cajones en
el heap
Hacemos un for para recorrer los cajones
Para cada cajon reservamos memoria para 50 cosas en el heap

*/
