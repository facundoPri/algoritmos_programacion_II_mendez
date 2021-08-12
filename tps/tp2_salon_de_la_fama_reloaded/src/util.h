#ifndef UTIL_H
#define UTIL_H

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define EXITO 0
#define NO_EXISTE NULL

/*
 * Recibe una string y devuelve una copia de ese string.
 */
char *duplicar_str(const char *string);

/**
 * Recibe una string y un valor separador. Devuelve una lista con los valores
 * separador o NULL en caso de error.
 * Hace una copia de string pasado, asi que este debe ser liberado por el usuario.
 */
lista_t *split(const char *str, char separador);

/**
 * Recibe una lista con string y libera la memoria utilizada
 */
void destruir_lista_split(lista_t*lista);

/**
 * Lee una linea completa de un archivo y devuelve un puntero al string leido.
 *
 * El string devuelto debe ser liberado con malloc.
 */
char *fgets_alloc(FILE *archivo);

/**
 * Recibe un archivo y un caracter separador. Devuelve una matriz (lista de
 * listas) donde se encuentra cada linea del archivo separada con el separador
 * pasado.
 */
lista_t *csv_reader(FILE *archivo, char separador);

/**
 * Recibe una lista creada por csv_reader y libera la memoria utilizada;
 */
void destruir_csv_lista(lista_t *csv_lista);

/**
 * Si el archivo no es nulo, lo cierra con fclose.
 */
void fclosen(FILE *archivo);

#endif /* UTIL_H */
