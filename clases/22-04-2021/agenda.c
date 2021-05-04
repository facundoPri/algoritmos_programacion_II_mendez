#include "agenda.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplicar_string(const char *texto) {
  char *duplicado = malloc(strlen(texto) * sizeof(char) + 1);
  if (!duplicado)
    return NULL;

  strcpy(duplicado, texto);

  return duplicado;
}

agenda_t *agenda_crear(const char *nombre) {
  agenda_t *agenda;
  agenda = calloc(1, sizeof(agenda_t));

  if (!agenda)
    return NULL;

  agenda->nombre = duplicar_string(nombre);

  if (!agenda->nombre) {
    free(agenda);
    return NULL;
  }

  return agenda;
}

agenda_t *agenda_agregar_contacto(agenda_t *agenda, const char *nombre,
                                  int telefono) {
  if (!agenda || !nombre || !*nombre || !telefono)
    return NULL;

  char *nombre_duplicado = duplicar_string(nombre);
  if (!nombre_duplicado)
    return NULL;

  void *aux =
      realloc(agenda->entradas,
              sizeof(item_agenda_t) * (size_t)(agenda->cantidad_entradas + 1));
  if (!aux) {
    free(nombre_duplicado);
    return NULL;
  }

  agenda->entradas = aux;

  /* item_agenda_t *item_aux = &agenda->entradas[agenda->cantidad_entradas]; */
  /* Otra dorma */
  /* agenda->entradas es la direccion del primer item , entonces le sumo la
   * cantidad de entradas existente para obtener la direccion de tal entrada */
  item_agenda_t *item = agenda->entradas + (agenda->cantidad_entradas);

  item->nombre = nombre_duplicado;
  item->numero = telefono;

  agenda->cantidad_entradas++;

  return agenda;
}

void agenda_mostrar(agenda_t *agenda) {
  if (!agenda)
    return;

  for (int i = 0; i < agenda->cantidad_entradas; i++) {
    printf("Nombre: %s, Numero: %i\n", agenda->entradas[i].nombre,
           agenda->entradas[i].numero);
  }
}

void agenda_mostrar_si(agenda_t *agenda, bool (*criterio)(item_agenda_t *)) {
  if (!agenda)
    return;

  for (int i = 0; i < agenda->cantidad_entradas; i++) {
    if (criterio(agenda->entradas + i))
      printf("Nombre: %s, Numero: %i\n", agenda->entradas[i].nombre,
             agenda->entradas[i].numero);
  }
}

void agenda_destruir(agenda_t *agenda) {
  free(agenda->nombre);

  for (int i = 0; i < agenda->cantidad_entradas; i++) {
    free(agenda->entradas[i].nombre);
  }

  free(agenda->entradas);
  free(agenda);
}
