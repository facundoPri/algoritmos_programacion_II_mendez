#include "abb.h"
#include <stdio.h>

abb_t *arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
  if (!comparador)
    return NULL;
  abb_t *arbol = calloc(1, sizeof(abb_t));
  arbol->comparador = comparador;
  arbol->destructor = destructor;
  return arbol;
}

nodo_abb_t *buscar_hoja(nodo_abb_t *nodo, abb_comparador comparador,
                        void *elemento) {
  int comparacion = comparador(nodo->elemento, elemento);
  if (comparacion > 0) {
    // elemento es menor al nodo
    if (nodo->izquierda == NULL) {
      // printf("izquierda NULL");
      return nodo->izquierda = calloc(1, sizeof(nodo_abb_t));
    }
    // printf("izquierda no NULL");
    return buscar_hoja(nodo->izquierda, comparador, elemento);
  } else if (comparacion <= 0) {
    // elmento es meyor al nodo
    if (nodo->derecha == NULL) {
      // printf("derecha NULL");
      return nodo->derecha = calloc(1, sizeof(nodo_abb_t));
    }
    // printf("derecha no NULL");
    return buscar_hoja(nodo->derecha, comparador, elemento);
  }
  return NULL;
}

int arbol_insertar(abb_t *arbol, void *elemento) {
  if (!arbol)
    return -1;

  if (arbol->nodo_raiz == NULL) {
    arbol->nodo_raiz = calloc(1, sizeof(nodo_abb_t));
    arbol->nodo_raiz->elemento = elemento;
    return 0;
  }
  nodo_abb_t *nuevo_nodo =
      buscar_hoja(arbol->nodo_raiz, arbol->comparador, elemento);
  nuevo_nodo->elemento = elemento;

  return 0;
}

int arbol_borrar(abb_t *arbol, void *elemento) { return 0; }

void *arbol_buscar(abb_t *arbol, void *elemento) { return 0; }

void *arbol_raiz(abb_t *arbol) { return 0; }

bool arbol_vacio(abb_t *arbol) { return 0; }

size_t arbol_recorrido_inorden(abb_t *arbol, void **array,
                               size_t tamanio_array) {
  return 0;
}
size_t arbol_recorrido_preorden(abb_t *arbol, void **array,
                                size_t tamanio_array) {
  return 0;
}
size_t arbol_recorrido_postorden(abb_t *arbol, void **array,
                                 size_t tamanio_array) {
  return 0;
}
void arbol_destruir(abb_t *arbol) {}

size_t abb_con_cada_elemento(abb_t *arbol, int recorrido,
                             bool (*funcion)(void *, void *), void *extra) {
  return 0;
}
