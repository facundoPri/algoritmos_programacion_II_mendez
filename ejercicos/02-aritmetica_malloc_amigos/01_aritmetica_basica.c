#include <stdio.h>

typedef struct {
  int a;
  char b;
  short c[20];
  double d;
} cosa;

int main() {
  int *puntero_int = NULL;
  char *puntero_char = NULL;
  cosa *puntero_cosa = 0;
  void *puntero_void = 0;

  /*
  Notacion
  puntero_cosa-> a == (*puntero_cosa).a
   */

  printf("P_c: %p, P_c+1: %p, P_c+2: %p\n", puntero_char, puntero_char + 1,
         puntero_char + 2);

  printf("P_i: %p, P_i+1: %p, P_i+2: %p\n", puntero_int, puntero_int + 1,
         puntero_int + 2);

  printf("P_cosa: %p, P_cosa+1: %p, P_cosa+2: %p\n", puntero_cosa,
         puntero_cosa + 1, puntero_cosa + 2);

  getchar();

  /* void pointer invalido */
  printf("P_v: %p, P_v+1: %p, P_v+2: %p\n", puntero_void, puntero_void + 1,
         puntero_void + 2);
}
