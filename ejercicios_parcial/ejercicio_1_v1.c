// Version 2
#include <stdlib.h>

typedef struct naranja {
  int numero;
  struct naranja *izquierda;
  struct naranja *centro;
  struct naranja *derecha;
} naranja_t;

int main() {
  naranja_t *inicial = calloc(1, sizeof(naranja_t));
  inicial->numero = 2;
  inicial->izquierda = calloc(1, sizeof(naranja_t));
  inicial->centro = calloc(1, sizeof(naranja_t));
  inicial->derecha = calloc(1, sizeof(naranja_t));

  inicial->izquierda->numero = 1;

  inicial->izquierda->izquierda = calloc(1, sizeof(naranja_t));
  inicial->izquierda->centro = calloc(1, sizeof(naranja_t));
  inicial->izquierda->derecha = calloc(1, sizeof(naranja_t));

  inicial->izquierda->izquierda->numero = 0;
  inicial->izquierda->centro->numero = 0;
  inicial->izquierda->derecha->numero = 0;

  inicial->centro->numero = 1;

  inicial->centro->izquierda = calloc(1, sizeof(naranja_t));
  inicial->centro->centro = calloc(1, sizeof(naranja_t));
  inicial->centro->derecha = calloc(1, sizeof(naranja_t));

  inicial->centro->izquierda->numero = 0;
  inicial->centro->centro->numero = 0;
  inicial->centro->derecha->numero = 0;

  inicial->derecha->numero = 1;

  inicial->derecha->izquierda = calloc(1, sizeof(naranja_t));
  inicial->derecha->centro = calloc(1, sizeof(naranja_t));
  inicial->derecha->derecha = calloc(1, sizeof(naranja_t));

  inicial->derecha->izquierda->numero = 0;
  inicial->derecha->centro->numero = 0;
  inicial->derecha->derecha->numero = 0;

  free(inicial->izquierda->izquierda);
  free(inicial->izquierda->centro);
  free(inicial->izquierda->derecha);
  free(inicial->centro->izquierda);
  free(inicial->centro->centro);
  free(inicial->centro->derecha);
  free(inicial->derecha->izquierda);
  free(inicial->derecha->centro);
  free(inicial->derecha->derecha);
  free(inicial->izquierda);
  free(inicial->centro);
  free(inicial->derecha);
  free(inicial);
}