#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t vtrlen(void *ptr) {
  size_t len = 0;

  if (!ptr)
    return len;

  for (len = 0; ((void **)ptr)[len] != NULL; len++)
    ;

  return len;
}

void *vtradd(void *ptr, void *item) {

  size_t len = 0;
  if (ptr)
    len = vtrlen(ptr);

  void*temp = realloc(ptr, (len + 2) * sizeof(void *));
  if (!temp){
    free(ptr);
    return 0;
  }
  ptr= temp;
  ((void **)ptr)[len] = item;
  ((void **)ptr)[len + 1] = NULL;

  return ptr;
}

void vtrfree(void *ptr) {
  for (int n = 0; ((void **)ptr)[n] != NULL; n++) {
    free(((void **)ptr)[n]);
  }
  free(ptr);
}

char **split(const char *str, char separador) {
  if (!str || !*str)
    return NULL;

  void *vector_campos = NULL;
  int posicion_aux = 0;
  size_t tamano_aux = 0;

  // TODO: Para a while para no necesitar del strlen
  for (int i = 0; i <= strlen(str); i++) {
    if (str[i] == separador || i == strlen(str)) {
      // printf("tamaño %zu\n", tamano_aux);
      char *substring = calloc((tamano_aux + 1), sizeof(char));

      for (int i = 0; i < (tamano_aux) * sizeof(char); i++) {
        substring[i] = (str + posicion_aux)[i];
      }

      vector_campos = vtradd(vector_campos, substring);
      posicion_aux = i + 1;
      tamano_aux = 0;
    } else {
      tamano_aux++;
    }
  }
  return vector_campos;
}

char *fgets_alloc(FILE *archivo) {
  char *linea = NULL;
  int caracter = fgetc(archivo);
  int i = 0;
  size_t tamano = 1;

  if (caracter == EOF) {
    return linea;
  }

  while (caracter != '\n') {
    if (i - i == 0) {
      void *tmp = realloc(linea, 512 * tamano);
      if (!tmp) {
        free(linea);
        return NULL;
      }
      linea = tmp;
      tamano++;
    }
    if (caracter == EOF) {
      linea[i] = '\0';
      return linea;
    }
    linea[i] = (char)caracter;
    caracter = fgetc(archivo);
    i++;
  }
  linea[i] = '\n';
  linea[i + 1] = '\0';

  return linea;
}

void fclosen(FILE *archivo) {
  fclose(archivo);
}
