#include "lista.h"
#include "pa2mm.h"

// Crear lista
void CuandoCreoLista_ObtengoPunteroListaConCantidad0YNodosEnNull() {
  lista_t *lista = lista_crear();

  pa2m_afirmar(lista->cantidad == 0, "La lista inicia con cantidad 0");
  pa2m_afirmar(lista->nodo_inicio == NULL,
               "La lista inicia con nodo_inicial nulo");
  pa2m_afirmar(lista->nodo_fin == NULL, "La lista inicia con nodo_fin nulo");

  free(lista);
}

// Insertar a Lista
void DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesObtengoUnaListaConCantidadIncrementada() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar(lista, elemento);

  pa2m_afirmar(lista->cantidad == 1, "La lista tiene cantidad igual a 1");

  lista_insertar(lista, elemento);
  pa2m_afirmar(lista->cantidad == 2, "La lista tiene cantidad igual a 2");

  lista_insertar(lista, elemento);
  pa2m_afirmar(lista->cantidad == 3, "La lista tiene cantidad igual a 3");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoInicialYFinalDeLaListaApuntanAlNodoDelElemento() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar(lista, elemento);

  pa2m_afirmar(lista->nodo_inicio->elemento == elemento,
               "El elemento del nodo_inicial corresponde al elemento pasado");
  pa2m_afirmar(lista->nodo_fin->elemento == elemento,
               "El elemento del nodo_fin corresponde al elemento pasado");

  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaNoVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoFinalDelaListaYElPenultimoNodoApuntanAlNodoDelElemento() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar(lista, elemento);
  void *nuevo_elemento = (void *)2;
  nodo_t *penultimo_nodo = lista->nodo_fin;
  lista_insertar(lista, nuevo_elemento);

  pa2m_afirmar(lista->nodo_fin->elemento == nuevo_elemento,
               "El elemento del nodo_final corresponde al elemento pasado");
  pa2m_afirmar(penultimo_nodo->siguiente == lista->nodo_fin,
               "El penultimo nodo apunta a nuevo nodo");

  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaInvalidaYUnElemento_CuandoIgresoElementoALista_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_insertar(NULL, (void *)1) == -1,
               "Devuelve -1 cuando lista es un elemento NULL")
}


int main() {
  pa2m_nuevo_grupo("Crear lista");
  CuandoCreoLista_ObtengoPunteroListaConCantidad0YNodosEnNull();

  pa2m_nuevo_grupo("Insertar a lista");
  DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesObtengoUnaListaConCantidadIncrementada();
  DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoInicialYFinalDeLaListaApuntanAlNodoDelElemento();
  DadaUnaListaNoVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoFinalDelaListaYElPenultimoNodoApuntanAlNodoDelElemento();


  return pa2m_mostrar_reporte();
}
