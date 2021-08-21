/*
Defina una estructura para implementar una lista doblemente enlazada. Muestre la
estructura e implemente las siguientes primitivas para la lista doblemente
enlazada:
- lista_crear
- lista_insertar_en_posicion
*/
typedef struct nodo {
  void *elemento;
  struct nodo *siguiente;
  struct nodo *anterior;
} nodo_t;

typedef struct lista {
  nodo_t *nodo_inicio;
  nodo_t *nodo_fin;
  size_t cantidad;
} lista_t;

/**
 * Crea una lista doblemente enlazada y devuelve un puntero a ella
 */
lista_t *lista_crear() {
  lista_t *lista = calloc(1, sizeof(lista_t));
  if (!lista) {
    return NULL;
  }

  return lista;
}

nodo_t *recorrer_nodos(nodo_t *nodo, size_t posicion) {
  if (posicion == 0 || nodo->siguiente == NULL) {
    return nodo;
  }
  return recorrer_nodos(nodo->siguiente, posicion - 1);
}

/**
 * Recibe lista, una posicion y un elemento, lo inserta en la posicion pasada.
 * Devuelve 0 en caso exito y -1 en caso de error
 */
int lista_insertar_en_posicion(lista_t *lista, size_t posicion,
                               void *elemento) {
  if (!lista)
    return -1;

  nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
  if (nuevo_nodo)
    return -1;

  if (posicion >= lista->cantidad) {
    lista->nodo_fin->siguiente = nuevo_nodo;
    nuevo_nodo->anterior = lista->nodo_fin;
    lista->nodo_fin = nuevo_nodo;
    return 0;
  }
  if (posicion == 0) {
    lista->nodo_inicio->anterior = nuevo_nodo;
    nuevo_nodo->siguiente = lista->nodo_inicio;
    lista->nodo_inicio = nuevo_nodo;
    return 0;
  }
  nodo_t *nodo_posicion = recorrer_nodos(lista->nodo_inicio, posicion);
  nodo_posicion->anterior->siguiente = nuevo_nodo;
  nuevo_nodo->anterior = nodo_posicion->anterior;
  nodo_posicion->anterior = nuevo_nodo;
  nuevo_nodo->siguiente = nodo_posicion;

  lista->cantidad++;
  return 0;
}

/* Version 2 */
/**
 * Recibe una lista y una posicion, elimina el elemento en la posicion pasada de
 * la lista. Devuelve 0 en caso de exito y -1 en caso de error
 */
int lista_eliminar_en_posicion(lista_t *lista, size_t posicion,
                               void *elemento) {
  if (!lista || lista->cantidad == 0)
    return -1;

  if (posicion >= lista->cantidad) {
    lista->nodo_fin->anterior = NULL;
    return 0;
  }
  if (posicion == 0) {
    if (lista->nodo_inicio->siguiente) {
      lista->nodo_inicio->siguiente->anterior = NULL;
      lista->nodo_inicio = lista->nodo_inicio->siguiente;
    } else {
      lista->nodo_inicio = NULL;
    }
    return 0;
  }
  nodo_t *nodo_posicion = recorrer_nodos(lista->nodo_inicio, posicion);
  nodo_posicion->siguiente->anterior = nodo_posicion->anterior;
  nodo_posicion->anterior->siguiente = nodo_posicion->siguiente;

  lista->cantidad--;
  return 0;
}
