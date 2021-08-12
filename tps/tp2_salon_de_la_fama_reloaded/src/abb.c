#include "abb.h"

abb_t *arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {
  if (!comparador)
    return NULL;
  abb_t *arbol = calloc(1, sizeof(abb_t));
  arbol->comparador = comparador;
  arbol->destructor = destructor;
  arbol->cantidad = 0;
  return arbol;
}

nodo_abb_t *buscar_hoja(nodo_abb_t *nodo, abb_comparador comparador,
                        void *elemento) {
  int comparacion = comparador(nodo->elemento, elemento);
  if (comparacion > 0) {
    // elemento es menor al nodo
    if (nodo->izquierda == NULL) {
      return nodo->izquierda = calloc(1, sizeof(nodo_abb_t));
    }
    return buscar_hoja(nodo->izquierda, comparador, elemento);
  } else if (comparacion <= 0) {
    // elmento es meyor al nodo
    if (nodo->derecha == NULL) {
      return nodo->derecha = calloc(1, sizeof(nodo_abb_t));
    }
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
    arbol->cantidad++;
    return 0;
  }
  nodo_abb_t *nuevo_nodo =
      buscar_hoja(arbol->nodo_raiz, arbol->comparador, elemento);
  if (!nuevo_nodo)
    return -1;
  nuevo_nodo->elemento = elemento;
  arbol->cantidad++;

  return 0;
}

nodo_abb_t *buscar_mayor_nodo(nodo_abb_t *nodo) {
  if (!nodo->derecha)
    return nodo;
  return buscar_mayor_nodo(nodo->derecha);
}

void destruir_nodo(nodo_abb_t *nodo, abb_liberar_elemento destructor) {
  if (destructor)
    destructor(nodo->elemento);
  free(nodo);
  nodo = NULL;
}

nodo_abb_t *borrar_nodo(nodo_abb_t *nodo, void *elemento,
                        abb_comparador comparador,
                        abb_liberar_elemento destructor) {
  if (!nodo)
    return NULL;
  int comparacion = comparador(nodo->elemento, elemento);
  if (comparacion > 0) {
    // Elemento es menor
    nodo->izquierda =
        borrar_nodo(nodo->izquierda, elemento, comparador, destructor);
  } else if (comparacion < 0) {
    // Elemento es mayor
    nodo->derecha =
        borrar_nodo(nodo->derecha, elemento, comparador, destructor);
  } else {
    // Este es el nodo a remover
    if (!nodo->izquierda && !nodo->derecha) {
      // No tiene hijos
      destruir_nodo(nodo, destructor);
      return NULL;
    }
    if (!nodo->izquierda || !nodo->derecha) {
      // Tiene un hijo
      nodo_abb_t *aux;
      if (!nodo->izquierda)
        aux = nodo->derecha;
      else if (!nodo->derecha)
        aux = nodo->izquierda;
      destruir_nodo(nodo, destructor);
      return aux;
    } else {
      // Tiene dos hijos
      // Encontrar el mayor nodo del sub arbol izquierdo
      nodo_abb_t *nodo_anterior_inorden = buscar_mayor_nodo(nodo->izquierda);

      // Remplazo el elemento del nodo_anterior_inorden con el del nodo actual
      if (destructor)
        destructor(nodo->elemento);
      nodo->elemento = nodo_anterior_inorden->elemento;

      // No quiero que se elimine elemento
      nodo->izquierda = borrar_nodo(
          nodo->izquierda, nodo_anterior_inorden->elemento, comparador, NULL);
    }
  }
  return nodo;
}

int arbol_borrar(abb_t *arbol, void *elemento) {
  if (!arbol)
    return -1;
  arbol->nodo_raiz = borrar_nodo(arbol->nodo_raiz, elemento, arbol->comparador,
                                 arbol->destructor);
  arbol->cantidad--;
  return 0;
}

nodo_abb_t *buscar_nodo(nodo_abb_t *nodo, abb_comparador comparador,
                        void *elemento) {
  if (!nodo || !elemento)
    return NULL;
  int comparacion = comparador(nodo->elemento, elemento);
  if (comparacion > 0) {
    return buscar_nodo(nodo->izquierda, comparador, elemento);
  } else if (comparacion < 0) {
    return buscar_nodo(nodo->derecha, comparador, elemento);
  } else
    return nodo;
}

void *arbol_buscar(abb_t *arbol, void *elemento) {
  if (!arbol)
    return NULL;
  nodo_abb_t *nodo_encontrado =
      buscar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);
  if (!nodo_encontrado)
    return NULL;
  return nodo_encontrado->elemento;
}

void *arbol_raiz(abb_t *arbol) {
  if (!arbol || !arbol->nodo_raiz)
    return NULL;
  return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t *arbol) {
  if (!arbol)
    return true;
  return arbol->nodo_raiz == NULL;
}

void recorrer_inorden(nodo_abb_t *nodo, size_t *index, void **array,
                      size_t tamanio_array) {
  if (!nodo)
    return;

  if (nodo->izquierda)
    recorrer_inorden(nodo->izquierda, index, array, tamanio_array);

  if ((*index) >= tamanio_array)
    return;

  array[*index] = nodo->elemento;
  (*index)++;

  if (nodo->derecha)
    recorrer_inorden(nodo->derecha, index, array, tamanio_array);

  return;
}

size_t arbol_recorrido_inorden(abb_t *arbol, void **array,
                               size_t tamanio_array) {
  if (!arbol || tamanio_array == 0)
    return 0;

  size_t index = 0;
  recorrer_inorden(arbol->nodo_raiz, &index, array, tamanio_array);
  return index;
}

void recorrer_preorden(nodo_abb_t *nodo, size_t *index, void **array,
                       size_t tamanio_array) {
  if (!nodo || (*index) >= tamanio_array)
    return;

  array[*index] = nodo->elemento;
  (*index)++;

  if (nodo->izquierda)
    recorrer_preorden(nodo->izquierda, index, array, tamanio_array);

  if (nodo->derecha)
    recorrer_preorden(nodo->derecha, index, array, tamanio_array);

  return;
}

size_t arbol_recorrido_preorden(abb_t *arbol, void **array,
                                size_t tamanio_array) {
  if (!arbol || tamanio_array == 0)
    return 0;

  size_t index = 0;
  recorrer_preorden(arbol->nodo_raiz, &index, array, tamanio_array);
  return index;
}

void recorrer_postorden(nodo_abb_t *nodo, size_t *index, void **array,
                        size_t tamanio_array) {
  if (!nodo)
    return;

  if (nodo->izquierda)
    recorrer_postorden(nodo->izquierda, index, array, tamanio_array);

  if (nodo->derecha)
    recorrer_postorden(nodo->derecha, index, array, tamanio_array);

  if ((*index) >= tamanio_array)
    return;
  array[*index] = nodo->elemento;
  (*index)++;

  return;
}

size_t arbol_recorrido_postorden(abb_t *arbol, void **array,
                                 size_t tamanio_array) {
  if (!arbol || tamanio_array == 0)
    return 0;

  size_t index = 0;
  recorrer_postorden(arbol->nodo_raiz, &index, array, tamanio_array);
  return index;
}

void nodo_destruir(nodo_abb_t *nodo, abb_liberar_elemento destructor) {
  if (!nodo)
    return;
  if (nodo->derecha)
    nodo_destruir(nodo->derecha, destructor);
  if (nodo->izquierda)
    nodo_destruir(nodo->izquierda, destructor);
  destruir_nodo(nodo, destructor);
}

void arbol_destruir(abb_t *arbol) {
  if (!arbol)
    return;
  nodo_destruir(arbol->nodo_raiz, arbol->destructor);
  free(arbol);
}

void abb_inorden_con_cada_elemento(nodo_abb_t *nodo,
                                   bool (*funcion)(void *, void *), void *extra,
                                   size_t *recorridos, bool *detener) {
  if (!nodo || *detener)
    return;

  if (nodo->izquierda || !*detener)
    abb_inorden_con_cada_elemento(nodo->izquierda, funcion, extra, recorridos,
                                  detener);

  if (!*detener) {
    (*detener) = (*funcion)(nodo->elemento, extra);
    (*recorridos)++;
  }

  if (nodo->derecha || !*detener)
    abb_inorden_con_cada_elemento(nodo->derecha, funcion, extra, recorridos,
                                  detener);

  return;
}
void abb_preorden_con_cada_elemento(nodo_abb_t *nodo,
                                    bool (*funcion)(void *, void *),
                                    void *extra, size_t *recorridos,
                                    bool *detener) {
  if (!nodo || *detener)
    return;

  if (!*detener) {
    (*detener) = (*funcion)(nodo->elemento, extra);
    (*recorridos)++;
  }

  if (nodo->izquierda || !*detener)
    abb_preorden_con_cada_elemento(nodo->izquierda, funcion, extra, recorridos,
                                   detener);

  if (nodo->derecha || !*detener)
    abb_preorden_con_cada_elemento(nodo->derecha, funcion, extra, recorridos,
                                   detener);

  return;
}
void abb_postorden_con_cada_elemento(nodo_abb_t *nodo,
                                     bool (*funcion)(void *, void *),
                                     void *extra, size_t *recorridos,
                                     bool *detener) {
  if (!nodo || *detener)
    return;

  if (nodo->izquierda || !*detener)
    abb_postorden_con_cada_elemento(nodo->izquierda, funcion, extra, recorridos,
                                    detener);

  if (nodo->derecha || !*detener)
    abb_postorden_con_cada_elemento(nodo->derecha, funcion, extra, recorridos,
                                    detener);

  if (!*detener) {
    (*detener) = (*funcion)(nodo->elemento, extra);
    (*recorridos)++;
  }

  return;
}

size_t abb_con_cada_elemento(abb_t *arbol, int recorrido,
                             bool (*funcion)(void *, void *), void *extra) {
  if (!arbol || !arbol->nodo_raiz || !funcion)
    return 0;
  size_t recorridos = 0;
  bool detener = false;
  switch (recorrido) {
  case ABB_RECORRER_INORDEN:
    abb_inorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra, &recorridos,
                                  &detener);
    break;
  case ABB_RECORRER_PREORDEN:
    abb_preorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra,
                                   &recorridos, &detener);
    break;
  case ABB_RECORRER_POSTORDEN:
    abb_postorden_con_cada_elemento(arbol->nodo_raiz, funcion, extra,
                                    &recorridos, &detener);
    break;
  }
  return recorridos;
}

size_t abb_cantidad(abb_t *arbol){
  if (!arbol)return 0;
  return arbol->cantidad;
}
