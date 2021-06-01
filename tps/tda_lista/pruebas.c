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

// Insertar a lista en posicion

void DadaUnaListaElementoYPosicion_CuandoIngresoElementoEnPosicion_EntoncesLaCantidadDeNodosSeIncrementa() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar_en_posicion(lista, elemento, 0);
  pa2m_afirmar(lista->cantidad == 1, "Cantidad de elementos igual a 1");

  lista_insertar_en_posicion(lista, elemento, 1);
  pa2m_afirmar(lista->cantidad == 2, "Cantidad de elementos igual a 2");

  lista_insertar_en_posicion(lista, elemento, 1);
  pa2m_afirmar(lista->cantidad == 3, "Cantidad de elementos igual a 3");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaUnElementoYZeroComoPosicion_CuandoIngresoElementoAListaEnPosicion_EntoncesSeLeAgregaElNodoDelElementoAlPrincipio() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar_en_posicion(lista, elemento, 0);
  pa2m_afirmar(lista->nodo_inicio->elemento == elemento,
               "Nuevo elemento agregado al principio, cuando lista vacia");

  lista_insertar_en_posicion(lista, elemento, 0);
  pa2m_afirmar(
      lista->nodo_inicio->elemento == elemento,
      "Nuevo elemento agregado al principio, cuando lista no esta vacia");
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaUnElementoYUnaPosicionMayorALaCantidad_CuandoIngresoElementoAListaEnPosicion_EntoncesSeAgregaNodoDelElementoAlFinal() {
  lista_t *lista = lista_crear();
  void *elemento = (void *)1;
  lista_insertar_en_posicion(lista, elemento, 10);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento,
               "Nuevo elemento agregado al final");

  free(lista->nodo_inicio);
  free(lista);
}

void DadaUnaListaUnElementoYUnaPosicionTresVeces_CuandoIngresoElementoAListaEnPosicion_EntoncesLaListaContieneTresNodosEnlazados() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;

  lista_insertar_en_posicion(lista, elemento_uno, 0);
  lista_insertar_en_posicion(lista, elemento_tres, 2);
  lista_insertar_en_posicion(lista, elemento_dos, 1);

  pa2m_afirmar(lista->nodo_inicio->elemento == elemento_uno,
               "El primer elemento corresponde");
  pa2m_afirmar(lista->nodo_inicio->siguiente->elemento == elemento_dos,
               "El segundo elemento corresponde");
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_tres,
               "El ultimo elemento corresponde");

  free(lista->nodo_inicio->siguiente->siguiente);
  free(lista->nodo_inicio->siguiente);
  free(lista->nodo_inicio);
  free(lista);
}

// Borrar ultimo elemento de lista
// Lista esta vacia
void DadaUnaListaVacia_CuandoIntentoBorrarElUltimoElemento_EntoncesObtengoMenosUno() {
  lista_t *lista = lista_crear();
  pa2m_afirmar(lista_borrar(lista) == -1,
               "Borrar ultimo elemento de lista vacia devuele -1");

  free(lista);
}
// Lista NULL
void DadaUnaListaNula_CuandoIntentoBorrarElUltimoElemento_EntoncesObtengoMenosUno() {
  pa2m_afirmar(lista_borrar(NULL) == -1,
               "Borrar ultimo elemento de lista Nula devuele -1");
}
// Borrar un elemento de la lista hace con que la cantidad disminuya
void DadaUnaLista_CuandoBorroElUltimoElemento_EntoncesLaCantidadDeNodosDisminuye() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  pa2m_afirmar(lista->cantidad == 3, "Lista contiene 3 nodos");
  lista_borrar(lista);
  pa2m_afirmar(lista->cantidad == 2, "Lista contiene 2 nodos");
  lista_borrar(lista);
  pa2m_afirmar(lista->cantidad == 1, "Lista contiene 1 nodo");
  lista_borrar(lista);
  pa2m_afirmar(lista->cantidad == 0, "Lista contiene 0 nodos");

  free(lista);
}

// Chequear que el ultimo elemento se borre
void DadaUnaLista_CuandoBorroElUltimoElemento_EntoncesLaListaCambiaDeUltimoElemento() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  void *elemento_dos = (void *)2;
  void *elemento_tres = (void *)3;
  // printf("%i",*(int*)lista->nodo_fin);
  lista_insertar(lista, elemento_uno);
  lista_insertar(lista, elemento_dos);
  lista_insertar(lista, elemento_tres);

  lista_borrar(lista);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_dos,
               "Al borrar el ultimo elemento, nodo_fin apunta al anterior [1]");
  lista_borrar(lista);
  pa2m_afirmar(lista->nodo_fin->elemento == elemento_uno,
               "Al borrar el ultimo elemento, nodo_fin apunta al anterior [2]");

  free(lista->nodo_inicio);
  free(lista);
}
// Borrar el ultimo elemento de una lista con un elemento hace que esta este
// vacia y los nodos apunten a null
void DadaUnaListaConUnElemento_CuandoBorroElUltimoElemento_EntoncesLaListaQuedaVaciaYConSusNodosApundandoANULL() {
  lista_t *lista = lista_crear();
  void *elemento_uno = (void *)1;
  lista_insertar(lista, elemento_uno);

  lista_borrar(lista);
  pa2m_afirmar(lista->nodo_inicio == NULL, "El nodo inicio apunta a NULL");
  pa2m_afirmar(lista->nodo_fin == NULL, "El nodo fin apunta a NULL");
  pa2m_afirmar(lista->cantidad == 0, "La cantidad de la lista es 0");

  free(lista);
}


int main() {
  pa2m_nuevo_grupo("Crear lista");
  CuandoCreoLista_ObtengoPunteroListaConCantidad0YNodosEnNull();

  pa2m_nuevo_grupo("Insertar a lista");
  DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesObtengoUnaListaConCantidadIncrementada();
  DadaUnaListaVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoInicialYFinalDeLaListaApuntanAlNodoDelElemento();
  DadaUnaListaNoVaciaYUnElemento_CuandoIngresoElementoALista_EntoncesElNodoFinalDelaListaYElPenultimoNodoApuntanAlNodoDelElemento();

  pa2m_nuevo_grupo("Insertar elemento en posicion");
  DadaUnaListaElementoYPosicion_CuandoIngresoElementoEnPosicion_EntoncesLaCantidadDeNodosSeIncrementa();
  DadaUnaListaUnElementoYZeroComoPosicion_CuandoIngresoElementoAListaEnPosicion_EntoncesSeLeAgregaElNodoDelElementoAlPrincipio();
  DadaUnaListaUnElementoYUnaPosicionMayorALaCantidad_CuandoIngresoElementoAListaEnPosicion_EntoncesSeAgregaNodoDelElementoAlFinal();
  DadaUnaListaUnElementoYUnaPosicionTresVeces_CuandoIngresoElementoAListaEnPosicion_EntoncesLaListaContieneTresNodosEnlazados();


  return pa2m_mostrar_reporte();
}
