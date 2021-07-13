#include "hash.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define ERROR -1
#define NO_EXISTE NULL
#define CAPACIDAD_MINIMA 3
#define IGUALES 0

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

/*
 * Recibe una string y devuelve la suma de cada uno de los caracteres.
 */
size_t funcion_hash(const char *clave) {
  size_t valor = 0;
  while (*clave) {
    valor += *clave++;
  }
  return valor;
}

/*
 * Recibe una string y devuelve una copia de ese string.
 */
char *duplicar_string(const char *s) {
  if (!s)
    return NO_EXISTE;

  char *p = malloc(strlen(s) + 1);
  if (!p)
    return NO_EXISTE;
  strcpy(p, s);
  return p;
}

/*
 * Recibe una clave string y un elemento para crear un puntero de tipo par_t y
 * devolverlo.
 */
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

/*
 * Recibe un hash, una lista de pares y el tamano de esa lista,
 * Inserta los elementos de la lista en el hash y devuelve 0 en exito o -1 en
 * error.
 */
int reinsertar_elementos(hash_t *hash, par_t **tabla, size_t capacidad_tabla) {
  for (int i = 0; i < capacidad_tabla; i++) {
    if (tabla[i]) {
      par_t *actual = tabla[i];
      int estado = hash_insertar(hash, actual->clave, actual->elemento);
      if (estado == ERROR)
        return ERROR;
    }
  }
  return EXITO;
}

/*
 * Recibe la funcion destructora de elementos, si existe, y el par a ser
 * eliminado Aplica la funcion destructora en el elemento y libera la memoria
 * usada.
 */
void destruir_par(hash_destruir_dato_t destructor, par_t *par) {
  if (destructor) {
    destructor(par->elemento);
  }
  free((void *)par->clave);
  free(par);
}

/*
 * Recibe la tabla se busca liberar de la memoria, el tamaño de esta tabla la
 * cantidad de elementos que se encuentra en la tabla y la funcion destructora.
 * Libera la memoria llamando destruir_par, para cada par y libera la tabla.
 */
void destruir_tabla(par_t **tabla, size_t capacidad_tabla,
                    size_t cantidad_elementos,
                    hash_destruir_dato_t destructor) {
  for (int i = 0; i < capacidad_tabla && cantidad_elementos != 0; i++) {
    if (tabla[i]) {
      par_t *actual = tabla[i];
      destruir_par(destructor, actual);
    }
  }
  free(tabla);
}

/*
 * Recibe un hash, duplica el tamaño de su tabla y reinserta los elementos que
 * antes estaban en la tabla, en caso de error el hash vuelve a su estado
 * anterior devuelve -1 en caso de error y 0 en caso de exito.
 */
int rehashear(hash_t *hash) {
  // Agrandar capacidad
  size_t capacidad_antigua = hash->capacidad;
  size_t cantidad_antigua = hash->cantidad;
  par_t **tabla_antigua = hash->tabla;

  hash->tabla = calloc(hash->capacidad * 2, sizeof(par_t));
  if (!hash->tabla) {
    hash->tabla = tabla_antigua;
    return ERROR;
  }
  hash->capacidad = hash->capacidad * 2;
  hash->cantidad = 0;

  // Reingresar elementos
  int estado = reinsertar_elementos(hash, tabla_antigua, capacidad_antigua);
  if (estado == ERROR) {
    // Devolver hash a su estado original
    destruir_tabla(hash->tabla, hash->capacidad, hash->cantidad, NULL);
    hash->tabla = tabla_antigua;
    hash->capacidad = capacidad_antigua;
    hash->cantidad = cantidad_antigua;
    return ERROR;
  }

  // Liberar tabla antigua
  destruir_tabla(tabla_antigua, capacidad_antigua, cantidad_antigua, NULL);

  return EXITO;
}

/*
 * Recibe un hash, una clave, y la posicion desde donde se empieza a buscar.
 * Devuelve el elemento encontrado con misma clave o NULL en caso que encuentre
 * un lugar vacio en la tabla del hash.
 */
par_t *buscar_elemento_desde_posicion(hash_t *hash, const char *clave,
                                      size_t posicion) {
  par_t *actual = hash->tabla[posicion];
  while (actual && strcmp(actual->clave, clave) != IGUALES) {
    posicion = (posicion + 1) % hash->capacidad;
    actual = hash->tabla[posicion];
  }
  return actual;
}

/*
 * Recibe un hash, una clave, y la posicion desde donde se empieza a buscar.
 * Devuelve la posicion donde se encuentra el elemento con misma clave o la
 * posicion donde se encontro un espacio libre en la memoria.
 */
size_t buscar_siguiente_elemento_posicion(hash_t *hash, const char *clave,
                                          size_t posicion) {
  par_t *actual = hash->tabla[posicion];
  while (actual && strcmp(actual->clave, clave) != IGUALES) {
    posicion = (posicion + 1) % hash->capacidad;
    actual = hash->tabla[posicion];
  }
  return posicion;
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
      return ERROR;
    hash->tabla[posicion] = par;
  } else {
    posicion = buscar_siguiente_elemento_posicion(hash, clave, posicion);
    par_t *actual = hash->tabla[posicion];

    if (actual) {
      actual->elemento = elemento;
      return EXITO;
    }
    par_t *par = crear_par(clave, elemento);
    if (!par)
      return ERROR;
    hash->tabla[posicion] = par;
  }
  hash->cantidad++;
  return EXITO;
}

/*
 * Recibe un hash y la posicion donde se borro un elemento
 * Busca elementos en la tabla que se encuentren fuera de orden, para rellenar
 * la posicion vacia. Hace esto con todos los elementos fuera de orden hasta
 * encontrarse con otro espacio vacio en la tabla del hash
 */
void reodenar_elementos_siguientes(hash_t *hash, size_t posicion) {
  size_t posicion_vacia = posicion;
  posicion++;
  par_t *actual = hash->tabla[posicion];
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
}

int hash_quitar(hash_t *hash, const char *clave) {
  if (!hash || !clave || hash->cantidad == 0)
    return ERROR;
  // Obtener posicion de elemento con funcion hash
  size_t clave_hash = funcion_hash(clave);
  size_t posicion = clave_hash % hash->capacidad;
  // Buscar elemento, ya que puede estar corrido
  // Si encuentra un lugar en blanco, valor no existe
  posicion = buscar_siguiente_elemento_posicion(hash, clave, posicion);
  par_t *actual = hash->tabla[posicion];

  if (!actual) {
    return ERROR;
  }
  // Borra elemento -> Ejecutar destuir elemento si existe
  destruir_par(hash->destructor, actual);
  hash->tabla[posicion] = NULL;
  hash->cantidad--;

  reodenar_elementos_siguientes(hash, posicion);

  return EXITO;
}

void *hash_obtener(hash_t *hash, const char *clave) {
  if (!hash || !clave)
    return NO_EXISTE;
  size_t clave_hash = funcion_hash(clave);
  size_t posicion = clave_hash % hash->capacidad;

  par_t *actual = buscar_elemento_desde_posicion(hash, clave, posicion);

  return actual ? actual->elemento : NO_EXISTE;
}

size_t hash_cantidad(hash_t *hash) {
  if (!hash)
    return 0;
  return hash->cantidad;
}

bool hash_contiene(hash_t *hash, const char *clave) {
  void *elemento_encontrado = hash_obtener(hash, clave);
  return elemento_encontrado;
}

void hash_destruir(hash_t *hash) {
  destruir_tabla(hash->tabla, hash->capacidad, hash->cantidad,
                 hash->destructor);
  free(hash);
}

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
  return cantidad_iterada;
}
