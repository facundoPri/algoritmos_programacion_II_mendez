#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//¿Como accedemos a la posicion 3,2 de la matriz?

void mostrar_matriz(int *mat, int w, int h);

int main() {

  int matriz[5][5];
  int *matriz2 = malloc(5 * 5 * sizeof(int));

  memset((void *)matriz, 0, 5 * 5 * sizeof(int));
  memset(matriz2, 0, 5 * 5 * sizeof(int));

  // Acceder el elemento [3][2]
  matriz[3][2];
  /* matriz2[5*fila+columna]; al ser un bloque de memoria tomamos como si
     fuera uno despues del otro*/
  matriz2[5 * 3 + 2];

  mostrar_matriz((int *)matriz, 5, 5);
  printf("\n");
  mostrar_matriz(matriz2, 5, 5);
}

// Nada que ver aqui

void mostrar_matriz(int *mat, int w, int h) {
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++)
      printf("%i ", mat[y * w + x]);
    printf("\n");
  }
}
