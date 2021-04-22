#include <stdio.h>
#include <stdlib.h>

//¿Que tiene de diferente esta matriz con las anteriores?

int main() {
  /* calloc me llena todos los valores de la memoria con 0
   * Y recibe primero la cantidad y despues el tamaño  */
  /* Al poner int** estoy diciento que estoy referenciando a un int* en cada
   * puntero */
  int **matriz = calloc(5, sizeof(int *));
  /* int** matriz = malloc(5*sizeof(int*)); */

  for (int i = 0; i < 5; i++)
    matriz[i] = calloc(5, sizeof(int));

  /* De esta forma podemos tener una matriz dinamica
   * que permite esta notacion */

  matriz[3][2] = 1;

  for (int y = 0; y < 5; y++) {
    for (int x = 0; x < 5; x++)
      printf("%i ", matriz[y][x]);
    printf("\n");
  }
}
