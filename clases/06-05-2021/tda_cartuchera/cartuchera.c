#include "cartuchera.h"

util_t *util_crear(tipo_util_t tipo);

void util_destruir(util_t *u);

cartuchera_t *cartuchera_crear(size_t capacidad) {
  if (capacidad == 0)
    return NULL;

  cartuchera_t *c = calloc(1, sizeof(cartuchera_t));
  if (!c)
    return NULL;
  c->capacidad = capacidad;

  return c;
}

void cartuchera_destruir(cartuchera_t *c) { free(c); }

size_t cartuchera_remover_utiles_desgastados(cartuchera_t *c,
                                             unsigned desgaste);
bool cartuchera_agregar_util(cartuchera_t *c, util_t *util);

size_t cartuchera_contrar_lapices(cartuchera_t *c);
