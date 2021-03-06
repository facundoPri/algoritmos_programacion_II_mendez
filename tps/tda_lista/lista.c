#include "lista.h"
#include <features.h>
#include <stdio.h>
#include <stdlib.h>

lista_t *lista_crear() {
  lista_t *lista = calloc(1, sizeof(lista_t));
  if (!lista) {
    return NULL;
  }

  return lista;
}

int lista_insertar(lista_t *lista, void *elemento) {
  if (!lista) {
    return -1;
  }
  nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
  if (!nuevo_nodo) {
    return -1;
  }

  nuevo_nodo->elemento = elemento;
  if (!lista->nodo_inicio) {
    lista->nodo_inicio = nuevo_nodo;
  } else {
    lista->nodo_fin->siguiente = nuevo_nodo;
  }

  lista->nodo_fin = nuevo_nodo;
  lista->cantidad++;

  return 0;
}

nodo_t *recorrer_nodos(nodo_t *nodo, size_t posicion) {
  if (posicion == 0 || nodo->siguiente == NULL) {
    return nodo;
  }
  return recorrer_nodos(nodo->siguiente, posicion - 1);
}

int lista_insertar_en_posicion(lista_t *lista, void *elemento,
                               size_t posicion) {
  if (!lista) {
    return -1;
  }
  nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
  if (!nuevo_nodo) {
    return -1;
  }
  nuevo_nodo->elemento = elemento;

  if (posicion >= lista->cantidad) {
    free(nuevo_nodo);
    return lista_insertar(lista, elemento);
  }

  if (posicion == (size_t)0) {
    nuevo_nodo->siguiente = lista->nodo_inicio;
    lista->nodo_inicio = nuevo_nodo;
  } else {
    nodo_t *nodo_anterior = recorrer_nodos(lista->nodo_inicio, posicion - 1);

    nuevo_nodo->siguiente = nodo_anterior->siguiente;
    nodo_anterior->siguiente = nuevo_nodo;
  }

  lista->cantidad++;
  return 0;
}

int lista_borrar(lista_t *lista) {
  if (!lista || lista->cantidad == 0) {
    return -1;
  }
  if (lista->cantidad == 1) {
    free(lista->nodo_fin);
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
  } else if (lista->cantidad == 2) {
    free(lista->nodo_fin);
    lista->nodo_fin = lista->nodo_inicio;
  } else {
    nodo_t *penultimo_nodo =
        recorrer_nodos(lista->nodo_inicio, lista->cantidad - 2);
    free(lista->nodo_fin);
    lista->nodo_fin = penultimo_nodo;
  }

  lista->cantidad--;
  return 0;
}

int lista_borrar_de_posicion(lista_t *lista, size_t posicion) {
  if (!lista || lista->cantidad == 0) {
    return -1;
  }
  if (lista->cantidad == 1) {
    free(lista->nodo_inicio);
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    lista->cantidad = 0;
    return 0;
  }
  if (posicion == 0) {
    nodo_t *nodo_borrar = lista->nodo_inicio;
    lista->nodo_inicio = nodo_borrar->siguiente;
    free(nodo_borrar);
  } else if (posicion >= lista->cantidad) {
    return lista_borrar(lista);
  } else {
    nodo_t *nodo_anterior = recorrer_nodos(lista->nodo_inicio, posicion - 1);
    nodo_t *nodo_borrar = nodo_anterior->siguiente;
    nodo_anterior->siguiente = nodo_borrar->siguiente;
    free(nodo_borrar);
  }
  lista->cantidad--;
  return 0;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion) {
  if (!lista || lista->cantidad < posicion + 1 || lista->cantidad == 0)
    return NULL;

  return recorrer_nodos(lista->nodo_inicio, posicion)->elemento;
}

void *lista_ultimo(lista_t *lista) {
  if (!lista || lista->cantidad == 0)
    return NULL;

  return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista) {
  if (!lista || (lista->cantidad == 0 && lista->nodo_inicio == NULL &&
                 lista->nodo_fin == NULL))
    return true;
  return false;
}

size_t lista_elementos(lista_t *lista) {
  if (!lista || lista->cantidad == 0)
    return 0;

  return lista->cantidad;
}

int lista_apilar(lista_t *lista, void *elemento) {
  return lista_insertar_en_posicion(lista, elemento, 0);
}

int lista_desapilar(lista_t *lista) {
  return lista_borrar_de_posicion(lista, 0);
}

void *lista_tope(lista_t *lista) {
  if (!lista || lista->cantidad == 0)
    return NULL;

  return lista->nodo_inicio->elemento;
}

int lista_encolar(lista_t *lista, void *elemento) {
  if (!lista) {
    return -1;
  }

  return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t *lista) {
  return lista_borrar_de_posicion(lista, 0);
}

void *lista_primero(lista_t *lista) {
  if (!lista || lista_vacia(lista))
    return NULL;
  return lista->nodo_inicio->elemento;
}

void lista_destruir(lista_t *lista) {
  if (!lista)
    return;
  size_t cantidad = lista->cantidad;
  for (size_t i = 0; i < cantidad; i++) {
    lista_borrar_de_posicion(lista, 0);
  }
  free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista) {
  if (!lista)
    return NULL;

  lista_iterador_t *lista_iterador = calloc(1, sizeof(lista_iterador_t));
  if (!lista_iterador)
    return NULL;

  lista_iterador->corriente = lista->nodo_inicio;
  lista_iterador->lista = lista;
  return lista_iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador) {
  if (!iterador)
    return false;
  if (!iterador->corriente)
    return false;
  return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador) {
  if (!iterador)
    return false;
  if (!iterador->corriente)
    return false;

  iterador->corriente = iterador->corriente->siguiente;
  if (!iterador->corriente)
    return false;
  return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador) {
  if (!iterador)
    return NULL;
  if (!iterador->corriente)
    return iterador->corriente;
  return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador) { free(iterador); }

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
                               void *contexto) {
  if (!lista || !funcion)
    return 0;
  size_t i = 0;
  nodo_t *nodo_actual = lista->nodo_inicio;
  while (nodo_actual) {
    i++;
    bool resultado = funcion(nodo_actual->elemento, contexto);
    if (!resultado) {
      break;
    }
    nodo_actual = nodo_actual->siguiente;
  }
  return i;
}
