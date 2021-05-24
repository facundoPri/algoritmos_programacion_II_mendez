#ifndef __CARTUCHERA_H_
#define __CARTUCHERA_H_

#include "util.h"
#include <stdlib.h>

typedef enum { LAPICERA, LAPIZ, GOMA } tipo_util_t;

typedef struct {
  tipo_util_t tipo;
  unsigned int desgaste;
} util_t;

typedef struct {
  size_t capacidad;
  util_t **utiles;
} cartuchera_t;

util_t *util_crear(tipo_util_t tipo);
void util_destruir(util_t *u);

cartuchera_t *cartuchera_crear(size_t capacidad);
void cartuchera_destruir(cartuchera_t *c);

// Saca los utiles con desgaste mayour o igual a desgaste y devuelve la cantidad
// de utiles que pudo sacar
size_t cartuchera_remover_utiles_desgastados(cartuchera_t *c,
                                             unsigned desgaste);
bool cartuchera_agregar_util(cartuchera_t *c, util_t *util);

size_t cartuchera_contrar_lapices(cartuchera_t *c);

#endif // __CARTUCHERA_H_
