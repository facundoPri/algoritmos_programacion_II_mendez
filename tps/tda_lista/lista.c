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

    return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    return NULL;
}

void* lista_ultimo(lista_t* lista){
    return NULL;
}

bool lista_vacia(lista_t* lista){
    return false;
}

size_t lista_elementos(lista_t* lista){
    return 0;
}

int lista_apilar(lista_t* lista, void* elemento){
    return 0;
}

int lista_desapilar(lista_t* lista){
    return 0;
}

void* lista_tope(lista_t* lista){
    return NULL;
}

int lista_encolar(lista_t* lista, void* elemento){
    return 0;
}

int lista_desencolar(lista_t* lista){
    return 0;
}

void* lista_primero(lista_t* lista){
    return NULL;
}

void lista_destruir(lista_t* lista){
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
        return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    return false;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    return false;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    return NULL;
}

void lista_iterador_destruir(lista_iterador_t* iterador){

}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    return 0;
}
