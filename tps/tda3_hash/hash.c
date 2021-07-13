#include "hash.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define ERROR -1
#define NO_EXISTE NULL
#define CAPACIDAD_MINIMA 3

const size_t FACTOR_CARGA = 75;

typedef struct par {
  void *elemento;
  const char *clave;
} par_t;

struct hash {
  size_t capacidad;
  size_t cantidad;
  hash_destruir_dato_t destructor;
  par_t **tabla;
};
// TODO: Modularizar/ Refactorizar mi codigo

hash_t *hash_crear(hash_destruir_dato_t destruir_elemento,
                   size_t capacidad_inicial) {
  if (capacidad_inicial < CAPACIDAD_MINIMA) {
    capacidad_inicial = CAPACIDAD_MINIMA;
  }
  hash_t *hash = calloc(1, sizeof(hash_t));
  if (!hash)
    return NO_EXISTE;
  hash->capacidad = capacidad_inicial;
  hash->destructor = destruir_elemento;
  hash->tabla = calloc(capacidad_inicial, sizeof(par_t));
  if (!hash->tabla) {
    free(hash);
    return NO_EXISTE;
  }
  return hash;
}

size_t funcion_hash(const char *clave) {
  size_t valor = 0;
  while (*clave) {
    valor += *clave++;
  }
  return valor;
}

char *duplicar_string(const char *s) {
  if (!s)
    return NO_EXISTE;

  char *p = malloc(strlen(s) + 1);
  if (!p)
    return NO_EXISTE;
  strcpy(p, s);
  return p;
}

par_t *crear_par(const char *clave, void *elemento) {
  par_t *par = malloc(sizeof(par_t));
  if (!par)
    return NO_EXISTE;
  par->clave = duplicar_string(clave);
  if (!par->clave) {
    free(par);
    return NO_EXISTE;
  }

  par->elemento = elemento;

  return par;
}
int rehashear(hash_t *hash) {
  // Agrandar capacidad
  size_t capacidad_antigua = hash->capacidad;
  par_t **tabla_antigua = hash->tabla;
  hash->tabla = calloc(hash->capacidad, sizeof(par_t));
  if (!hash->tabla) {
    hash->tabla = tabla_antigua;
    return ERROR;
  }
  hash->capacidad = capacidad_antigua * 2;
  // Reingresar elementos
  hash->cantidad = 0;

  // Liberar tabla antigua
  for (int i = 0; i < capacidad_antigua; i++) {
    if (tabla_antigua[i]) {
      par_t *actual = tabla_antigua[i];
      int estado = hash_insertar(hash, actual->clave, actual->elemento);
      if (estado == ERROR) {
        // TODO: Volver a la tabla anterior y liberar la nueva tabla
        return ERROR;
      }

      free((void *)actual->clave);
      free(actual);
    }
  }
  free(tabla_antigua);
  return EXITO;
}

int hash_insertar(hash_t *hash, const char *clave, void *elemento) {
  if (!hash || !clave)
    return -1;

  // Rehash
  if ((((float)(hash->cantidad + 1) / (float)hash->capacidad) * 100) > 75) {
    int estado = rehashear(hash);
    if (estado)
      return ERROR;
  }

  size_t clave_hash = funcion_hash(clave);
  size_t posicion = clave_hash % hash->capacidad;

  if (!hash->tabla[posicion]) {
    par_t *par = crear_par(clave, elemento);
    if (!par)
      return -1;
    hash->tabla[posicion] = par;
  } else {
    par_t *actual = hash->tabla[posicion];
    while (actual && strcmp(actual->clave, clave) != 0) {
      posicion = (posicion + 1) % hash->capacidad;
      actual = hash->tabla[posicion];
    }
    if (actual) {
      actual->elemento = elemento;
      return EXITO;
    }
    par_t *par = crear_par(clave, elemento);
    if (!par)
      return -1;
    hash->tabla[posicion] = par;
  }
  hash->cantidad++;
  return EXITO;
}

int hash_quitar(hash_t *hash, const char *clave) {
  if (!hash || !clave || hash->cantidad == 0)
    return ERROR;
  // Obtener posicion de elemento con funcion hash
  size_t clave_hash = funcion_hash(clave);
  size_t posicion = clave_hash % hash->capacidad;
  // Buscar elemento, ya que puede estar corrido
  // Si encuentra un lugar en blanco, valor no existe
  par_t *actual = hash->tabla[posicion];
  while (actual && strcmp(actual->clave, clave) != 0) {
    posicion = (posicion + 1) % hash->capacidad;
    actual = hash->tabla[posicion];
  }
  if (!actual) {
    return ERROR;
  }
  // Borra elemento -> Ejecutar destuir elemento si existe
  if (hash->destructor) {
    hash->destructor(hash->tabla[posicion]->elemento);
  }
  free((void *)hash->tabla[posicion]->clave);
  free(hash->tabla[posicion]);
  hash->tabla[posicion] = NULL;

  hash->cantidad--;
  size_t posicion_vacia = posicion;
  posicion++;
  actual = hash->tabla[posicion];
  // Verificar hasta encontrar un espacio en blanco
  while (actual) {
    // Verificar si el elemento de abajo esta corrido
    size_t clave_hash = funcion_hash(actual->clave);
    size_t posicion_hash = clave_hash % hash->capacidad;

    // Si el elemento de abajo esta corrido entonces moverlo para arriba y
    if (posicion != posicion_hash && posicion_vacia >= posicion_hash) {
      hash->tabla[posicion_vacia] = actual;
      hash->tabla[posicion] = NULL;
      posicion_vacia = posicion;
    }

    posicion = (posicion + 1) % hash->capacidad;
    actual = hash->tabla[posicion];
  }
  return EXITO;
}

void *hash_obtener(hash_t *hash, const char *clave) {
  if (!hash || !clave)
    return NO_EXISTE;
  size_t clave_hash = funcion_hash(clave);
  size_t posicion = clave_hash % hash->capacidad;

  par_t *actual = hash->tabla[posicion];
  while (actual && strcmp(actual->clave, clave) != 0) {
    posicion = (posicion + 1) % hash->capacidad;
    actual = hash->tabla[posicion];
  }

  return actual ? actual->elemento : NO_EXISTE;
}

size_t hash_cantidad(hash_t *hash) {
  if (!hash)
    return 0;
  return hash->cantidad;
}

// TODO: Cuando tenga la funcion para iterar los elementos mejor utilizarla a
// esa misma
bool hash_contiene(hash_t *hash, const char *clave) {
  void *elemento_encontrado = hash_obtener(hash, clave);
  return elemento_encontrado;
}

void destruir_tabla(hash_t *hash) {
  for (int i = 0; i < hash->capacidad || hash->cantidad > 0; i++) {
    if (hash->tabla[i]) {
      par_t *actual = hash->tabla[i];
      if (hash->destructor) {
        hash->destructor(actual->elemento);
      }
      free((void *)actual->clave);
      free(actual);
      hash->cantidad--;
    }
  }
  free(hash->tabla);
}

void hash_destruir(hash_t *hash) {
  destruir_tabla(hash);
  free(hash);
}

// TODO: Refactorar secciones de codigo con esta funcion
size_t hash_con_cada_clave(hash_t *hash,
                           bool (*funcion)(hash_t *hash, const char *clave,
                                           void *aux),
                           void *aux) {
  if (!hash || hash->cantidad == 0)
    return 0;
  bool detener_iterador = false;
  size_t cantidad_iterada = 0;
  for (int i = 0; i < hash->capacidad && !detener_iterador; i++) {
    if (hash->tabla[i]) {
      par_t *actual = hash->tabla[i];
      if (funcion)
        detener_iterador = funcion(hash, actual->clave, aux);
      cantidad_iterada++;
    }
  }
  // detener_iterador = detener_iterador;
  return cantidad_iterada;
}
