#include "util.h"

/*
 * Recibe una string y devuelve una copia de ese string.
 */
char *duplicar_str(const char *string) {
  if (!string)
    return NO_EXISTE;

  char *p = malloc(strlen(string) + 1);
  if (!p)
    return NO_EXISTE;
  strcpy(p, string);
  return p;
}


lista_t *split(const char *str, char separador) {
  if (!str )
    return NULL;

  lista_t *lista_campos = lista_crear();
  if (!lista_campos)
    return NULL;

  int posicion_aux = 0;
  size_t tamano_aux = 0;


  // TODO: mejorar esto
  if (strlen(str) == 0) {
    int resultado = lista_insertar(lista_campos, duplicar_str(str));
    if (resultado == ERROR) {
      lista_destruir(lista_campos);
      return NULL;
    }
    return lista_campos;
  }

  // TODO: Para a while para no necesitar del strlen
  for (int i = 0; i <= strlen(str); i++) {
    if (str[i] == separador || i == strlen(str)) {
      char *substring = calloc((tamano_aux + 1), sizeof(char));

      for (int i = 0; i < (tamano_aux) * sizeof(char); i++) {
        substring[i] = (str + posicion_aux)[i];
      }

      int resultado = lista_insertar(lista_campos, duplicar_str(substring));
      if (resultado == ERROR) {
        lista_destruir(lista_campos);
        return NULL;
      }
      free(substring);
      posicion_aux = i + 1;
      tamano_aux = 0;
    } else {
      tamano_aux++;
    }
  }
  return lista_campos;
}

bool destruir_string(void *string, void *contexto) {
  contexto = contexto;
  free(string);
  return true;
}

void destruir_lista_split(lista_t *lista) {
  lista_con_cada_elemento(lista, destruir_string, NULL);
  lista_destruir(lista);
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

void fclosen(FILE *archivo) { fclose(archivo); }

lista_t *csv_reader(FILE *archivo, char separador) {
  if (!archivo || !separador)
    return NULL;
  lista_t *lista_archivo = lista_crear();
  if (!lista_archivo)
    return NULL;
  char *linea = NULL;

  while ((linea = fgets_alloc(archivo))) {
    lista_t *lista_linea = split(linea, separador);
    free(linea);
    if (!lista_linea) {
      destruir_csv_lista(lista_archivo);
      return NULL;
    }
    int resultado = lista_insertar(lista_archivo, lista_linea);
    if (resultado == ERROR) {
      destruir_csv_lista(lista_archivo);
      return NO_EXISTE;
    }
  }
  return lista_archivo;
};


bool destruir_lista_split_csv(void *lista, void *contexto) {
  contexto = contexto;
  destruir_lista_split(lista);
  return true;
}

void destruir_csv_lista(lista_t *csv_lista) {
  lista_con_cada_elemento(csv_lista, destruir_lista_split_csv, NULL);
  lista_destruir(csv_lista);
};
