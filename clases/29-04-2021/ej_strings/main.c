#include <stdio.h>

void imprimir_invertido(char *texto) {
  if (!*texto)
    return;
  /* if (texto[0] == 0) */
  /*   return; */

  imprimir_invertido(texto + 1);
  printf("%c", *texto);
  /* printf("%c", texto[0]); */
}

void imprimir_divertido(char *texto, int flag) {
  if (!*texto)
    return;

  if (*texto == ' ' || flag) {

    imprimir_divertido(texto + 1, 1);
    printf("%c", *texto);

  } else {

    printf("%c", *texto);
    imprimir_divertido(texto + 1, 0);
  }
}

int main() {
  char *texto = "Hola Mundo!";
  imprimir_invertido(texto);
  printf("\n");
  imprimir_divertido(texto, 0);

  /* Incrementar antes de ejecucion y despues de ejecucion */
  int i = 0;
  int j = 0;
  printf("\n");
  printf("i vale %i y j vale %i\n", i++, ++j);
  printf("i vale %i y j vale %i\n", i, j);

  return 0;
}
