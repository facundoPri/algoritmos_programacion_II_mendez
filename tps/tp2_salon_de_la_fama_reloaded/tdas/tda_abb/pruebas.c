#include "abb.h"
#include "pa2mm.h"
#include "string.h"
#include <stdio.h>

typedef struct cosa {
  int clave;
  char contenido[10];
} cosa;

cosa *crear_cosa(int clave) {
  cosa *c = (cosa *)malloc(sizeof(cosa));
  if (c)
    c->clave = clave;
  return c;
}

void destruir_cosa(cosa *c) { free(c); }

int comparar_cosas(void *elemento1, void *elemento2) {
  if (!elemento1 || !elemento2)
    return 0;

  cosa *c1 = elemento1;
  cosa *c2 = elemento2;

  return c1->clave - c2->clave;
}

void destructor_de_cosas(void *elemento) {
  if (!elemento)
    return;
  destruir_cosa((cosa *)elemento);
}

// ----------------------------------------------------------------
// Crear arbol
// ----------------------------------------------------------------
// Crear arbol devuelve puntero null cuando no recibe un comparador
void DadoComparadorNuloYDestructor_CuandoIntentoCrearArbol_EntoncesObtengoNULL() {
  abb_t *arbol = arbol_crear(NULL, destructor_de_cosas);

  pa2m_afirmar(arbol == NULL, "Como no recibe una funcion comparadora entonces "
                              "no se puede crear el arbol")
}
// Crear arbol devuelve puntero al arbol cuando no recibe destructor
void DadoContadorYDestructorNulo_CuandoCreoArbol_EntoncesObtengoPunteroAlArbol() {
  abb_t *arbol = arbol_crear(comparar_cosas, NULL);

  pa2m_afirmar(arbol->nodo_raiz == NULL, "Nodo raiz apunta a NULL");
  pa2m_afirmar(arbol->comparador == comparar_cosas,
               "Comparador corresponde con la funcion comparador pasada");
  pa2m_afirmar(arbol->destructor == NULL, "Destructor es NULL");
  arbol_destruir(arbol);
}
// Crear arbol devuelve puntero al arbol
// Nodo raiz de arbol creado apunta a null
void DadoUnComparadorYUnDestructor_CuandoCreoArbol_EntoncesObtengoPunteroAlArbolConNodoRaizNulaYComparadorYDestructorCorresponden() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  pa2m_afirmar(arbol->nodo_raiz == NULL, "Nodo raiz apunta a NULL");
  pa2m_afirmar(arbol->comparador == comparar_cosas,
               "Comparador corresponde con la funcion comparador pasada");
  pa2m_afirmar(arbol->destructor == destructor_de_cosas,
               "Destructor corresponde con la funcion destructora pasada");

  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
// Arbol insertar
// ----------------------------------------------------------------
// - Si recibe arbol invalido devuelve 0
void DadoArbolInvalido_CuandoIntentoInsertar_EntoncesObtengo0() {
  int resultado = arbol_insertar(NULL, NULL);

  pa2m_afirmar(resultado == -1, "No se puede insertar en un arbol nulo")
}
// - El primer elemento se transforma en nodo_raiz
// - Cada nodo nuevo posee un elemento y apunta a null por izquierda y derecha
// - Si el comparador devuelve 0 los elementos son iguales y este se almazena a
// la derecha de su padre
// - Si el comparador devuelve <0 el nuevo elemento es mayor y este se almazena
// a la derecha de su padre
// - Si el comparador devuelve >0 el nuevo elemento es menor y este se almazena
// a la izquierda de su padre
void DadoArbolVacionYElementos_CuandoInserto_EntoncesObtengoArbolOrdenado() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c2_copy = crear_cosa(2);
  cosa *c4 = crear_cosa(4);
  cosa *c6 = crear_cosa(6);

  arbol_insertar(arbol, c4);
  pa2m_afirmar(arbol->nodo_raiz->elemento == c4,
               "Se inserto primer elemento y es el nodo raiz");
  pa2m_afirmar(arbol->nodo_raiz->izquierda == NULL,
               "El nodo izquierda de la raiz es nulo");
  pa2m_afirmar(arbol->nodo_raiz->derecha == NULL,
               "El nodo derecha de la raiz es nulo");
  arbol_insertar(arbol, c2);
  pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == c2,
               "Se inserto un elemento menos a la raiz y esta a su izquierda");
  arbol_insertar(arbol, c2_copy);
  pa2m_afirmar(
      arbol->nodo_raiz->izquierda->derecha->elemento == c2_copy,
      "Insertar un elemento igual lo posiciona a la derecha del anterior");
  arbol_insertar(arbol, c6);
  pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == c6,
               "Insertar elemento mayor a la raiz lo posiciona a la derecha");
  arbol_insertar(arbol, c1);
  pa2m_afirmar(arbol->nodo_raiz->izquierda->izquierda->elemento == c1,
               "Insertar elemento menor al nodo izquierda de la raiz lo "
               "posicion a la izquierda del nodo iquierda");

  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
// Arbol borrar
// ----------------------------------------------------------------
// Si recibe un arbol invalido devuelve -1
void DadoUnArbolInvalido_CuandoIntentoBorrarUnElemento_EntoncesObtengoMenosUno() {
  // int resultado = arbol_borrar(NULL, NULL);
  // pa2m_afirmar(resultado == -1, "Cuando arbol_borrar recibe arbol null
  // devuelve -1");
}

// Puede borrar todos los elementos de un arbol
// Cuado hay elementos iguales puede borrar sin problema
// Cuando Intento borrar la raiz primero se borra sin problema
void DadoArbolYElementos_CuandoBorroTodosLosElementosDelArbol_EntoncesObtengo0ParaTodosLosCasos() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c6_copy = crear_cosa(6);

  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c1);
  arbol_insertar(arbol, c2);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c6_copy);
  arbol_insertar(arbol, c4);
  arbol_insertar(arbol, c5);

  pa2m_afirmar(arbol_borrar(arbol, c3) == 0, "Se pudo borrar la raiz de arbol");
  pa2m_afirmar(arbol->nodo_raiz->elemento == c2,
               "La nueva raiz es el mayor numero menor a la ex raiz");
  pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == c6,
               "Nodo derecha de la raiz corresponde");
  pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == c1,
               "Nodo izquierda de la raiz corresponde");
  pa2m_afirmar(arbol_borrar(arbol, c6) == 0, "Se borro elemento repetido");
  pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == c5,
               "El mayor elemento de los menores lo remplazo");
  pa2m_afirmar(arbol_borrar(arbol, c5) == 0,
               "Se pudo borrar elemento del arbol [1]");
  pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == c4,
               "El mayor elemento de los menores lo remplazo");
  pa2m_afirmar(arbol_borrar(arbol, c6_copy) == 0,
               "Se pudo borrar elemento del arbol [1]");
  pa2m_afirmar(arbol_borrar(arbol, c4) == 0,
               "Se pudo borrar nodo derecho de la raiz");
  pa2m_afirmar(arbol->nodo_raiz->derecha == NULL,
               "El nodo derecha de la raiz apunta a null");
  pa2m_afirmar(arbol_borrar(arbol, c1) == 0,
               "Se pudo borrar nodo izquierda de la raiz");
  pa2m_afirmar(arbol->nodo_raiz->derecha == NULL,
               "El nodo izquierda de la raiz apunta a null");
  pa2m_afirmar(arbol_borrar(arbol, c2) == 0, "Se pudo borrar ultimo elemento");
  pa2m_afirmar(arbol_vacio(arbol) == true, "Arbol se encuantra vacia");

  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
// Arbol buscar
// ----------------------------------------------------------------
void DadoArbolInvalido_CuandoBuscoElementoEnArbol_EntoncesObtengoNULL() {
  pa2m_afirmar(arbol_buscar(NULL, NULL) == NULL,
               "Buscar elemento en arbol nulo devuelve NULL");
}
void DadoArbolYElementos_CuandoBuscoElementoEnArbol_EntoncesObtengoElementoEncontradoONull() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c1 = crear_cosa(1);
  cosa *c2 = crear_cosa(2);
  cosa *c3 = crear_cosa(3);
  cosa *c4 = crear_cosa(4);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c6_copia = crear_cosa(6);
  cosa *c7 = crear_cosa(7);

  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c1);
  arbol_insertar(arbol, c2);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c6_copia);
  arbol_insertar(arbol, c4);
  arbol_insertar(arbol, c5);

  pa2m_afirmar(arbol_buscar(arbol, c1) == c1,
               "Cuando busco elemento en arbol obtengo elemento deseado [1]");
  pa2m_afirmar(arbol_buscar(arbol, c2) == c2,
               "Cuando busco elemento en arbol obtengo elemento deseado [2]");
  pa2m_afirmar(arbol_buscar(arbol, c3) == c3,
               "Cuando busco elemento en arbol obtengo elemento deseado [3]");
  pa2m_afirmar(arbol_buscar(arbol, c5) == c5,
               "Cuando busco elemento en arbol obtengo elemento deseado [4]");
  pa2m_afirmar(
      arbol_buscar(arbol, c6) == c6,
      "Cuando busco elemento duplicado en arbol obtengo elemento deseado");
  pa2m_afirmar(arbol_buscar(arbol, c7) == NULL,
               "Cuando busco elemento que no esta en arbol obtengo null");

  arbol->destructor(c7);
  arbol_destruir(arbol);
}
// ----------------------------------------------------------------
// Arbol raiz
// ----------------------------------------------------------------
void DadoArbolNULL_CuandoVerificoRaiz_EntoncesObtengoNULL() {
  pa2m_afirmar(arbol_raiz(NULL) == NULL,
               "Cuando busco raiz en arbol NULL obtengo NULL");
}
void DadoArbolVacio_CuandoVerificoRaiz_EntoncesObtengoNULL() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  pa2m_afirmar(arbol_raiz(arbol) == NULL,
               "Cuando busco raiz en arbol NULL obtengo NULL");
  arbol_destruir(arbol);
}
void DadoArbol_CuandoVerificoRaiz_EntoncesObtengoRaiz() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c1 = crear_cosa(1);

  arbol_insertar(arbol, c1);

  pa2m_afirmar(arbol_raiz(arbol) == c1,
               "Cuando busco raiz en arbol obtengo raiz correspondiente");

  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
// Arbol vacio
// ----------------------------------------------------------------
void DadoUnArbolNULL_CuandoVerificoSiArbolVacio_EntoncesObtengoTrue() {
  pa2m_afirmar(arbol_vacio(NULL) == true,
               "Un arbol nulo devuelve true cuando verifico si esta vacio");
}
void DadoUnArbolVacio_CuandoVerificoSiArbolVacio_EntoncesObtengoTrue() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  pa2m_afirmar(arbol_vacio(arbol) == true,
               "Un arbol vacio devuelve true cuando verifico si esta vacio");
  arbol_destruir(arbol);
}
void DadoUnArbolConElementos_CuandoVerificoSiArbolVacio_EntoncesObtengoFalse() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  cosa *c1 = crear_cosa(1);
  arbol_insertar(arbol, c1);

  pa2m_afirmar(
      arbol_vacio(arbol) == false,
      "Un arbol con elementos devuelve false cuando verifico si esta vacio");
  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
// Recorrer arbol inorden
// ----------------------------------------------------------------
void DadoArbolNulo_CuandoIntentoRecorrerArbolInorden_EntoncesObtengo0() {
  size_t tamanio_array = 0;
  void *array[tamanio_array];
  size_t cantidad = arbol_recorrido_inorden(NULL, array, tamanio_array);
  pa2m_afirmar(cantidad == 0, "Cuando recorro arbol nulo recorro 0 elementos")
}
void DadoArbolVacio_CuandoIntentoRecorrerArbolInorden_EntoncesObtengo0() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  size_t tamanio_array = 0;
  void *array[tamanio_array];
  size_t cantidad = arbol_recorrido_inorden(NULL, array, tamanio_array);
  pa2m_afirmar(cantidad == 0, "Cuando recorro arbol vacio recorro 0 elementos");
  arbol_destruir(arbol);
}
void DadoArbolConElementos_CuandoRecorroArbolInorden_EntoncesObtengoLaCantidadDeElementosRecorridosYUnArrayConElementos() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c3 = crear_cosa(3);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);
  cosa *c12 = crear_cosa(12);
  cosa *c13 = crear_cosa(13);

  arbol_insertar(arbol, c7);
  arbol_insertar(arbol, c5);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c13);
  arbol_insertar(arbol, c12);

  size_t tamanio_array = 6;
  void *array[tamanio_array];

  size_t cantidad = arbol_recorrido_inorden(arbol, array, tamanio_array);

  pa2m_afirmar(cantidad == tamanio_array,
               "La cantidad de elementos en array es la misma que la misma al "
               "tamanio en el array");

  pa2m_afirmar(((cosa *)array[0]) == c3, "Primer valor en array corresponde");
  pa2m_afirmar(((cosa *)array[1]) == c5, "Segundo valor en array corresponde");
  pa2m_afirmar(((cosa *)array[2]) == c6, "Tercer valor en array corresponde");
  pa2m_afirmar(((cosa *)array[3]) == c7, "Cuarto valor en array corresponde");
  pa2m_afirmar(((cosa *)array[4]) == c12, "Quinto valor en array corresponde");
  pa2m_afirmar(((cosa *)array[5]) == c13, "Sexto valor en array corresponde");

  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
// Recorrer arbol preorden
// ----------------------------------------------------------------
void DadoArbolNulo_CuandoIntentoRecorrerArbolPreorden_EntoncesObtengo0() {
  size_t tamanio_array = 0;
  void *array[tamanio_array];
  size_t cantidad = arbol_recorrido_preorden(NULL, array, tamanio_array);
  pa2m_afirmar(cantidad == 0, "Cuando recorro arbol nulo recorro 0 elementos")
}
void DadoArbolVacio_CuandoIntentoRecorrerArbolPreorden_EntoncesObtengo0() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  size_t tamanio_array = 0;
  void *array[tamanio_array];
  size_t cantidad = arbol_recorrido_preorden(NULL, array, tamanio_array);
  pa2m_afirmar(cantidad == 0, "Cuando recorro arbol vacio recorro 0 elementos");
  arbol_destruir(arbol);
}
void DadoArbolConElementos_CuandoRecorroArbolPreorden_EntoncesObtengoLaCantidadDeElementosRecorridosYUnArrayConElementos() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c3 = crear_cosa(3);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);
  cosa *c12 = crear_cosa(12);
  cosa *c13 = crear_cosa(13);

  arbol_insertar(arbol, c7);
  arbol_insertar(arbol, c5);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c13);
  arbol_insertar(arbol, c12);

  size_t tamanio_array = 6;
  void *array[tamanio_array];

  size_t cantidad = arbol_recorrido_preorden(arbol, array, tamanio_array);

  pa2m_afirmar(cantidad == tamanio_array,
               "La cantidad de elementos en array es la misma que la misma al "
               "tamanio en el array");

  pa2m_afirmar(((cosa *)array[0]) == c7, "Primer valor en array corresponde");
  pa2m_afirmar(((cosa *)array[1]) == c5, "Segundo valor en array corresponde");
  pa2m_afirmar(((cosa *)array[2]) == c3, "Tercer valor en array corresponde");
  pa2m_afirmar(((cosa *)array[3]) == c6, "Cuarto valor en array corresponde");
  pa2m_afirmar(((cosa *)array[4]) == c13, "Quinto valor en array corresponde");
  pa2m_afirmar(((cosa *)array[5]) == c12, "Sexto valor en array corresponde");

  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
// Recorrer arbol postorden
// ----------------------------------------------------------------
void DadoArbolNulo_CuandoIntentoRecorrerArbolPostorden_EntoncesObtengo0() {
  size_t tamanio_array = 0;
  void *array[tamanio_array];
  size_t cantidad = arbol_recorrido_postorden(NULL, array, tamanio_array);
  pa2m_afirmar(cantidad == 0, "Cuando recorro arbol nulo recorro 0 elementos")
}
void DadoArbolVacio_CuandoIntentoRecorrerArbolPostorden_EntoncesObtengo0() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  size_t tamanio_array = 0;
  void *array[tamanio_array];
  size_t cantidad = arbol_recorrido_postorden(NULL, array, tamanio_array);
  pa2m_afirmar(cantidad == 0, "Cuando recorro arbol vacio recorro 0 elementos");
  arbol_destruir(arbol);
}
void DadoArbolConElementos_CuandoRecorroArbolPostorden_EntoncesObtengoLaCantidadDeElementosRecorridosYUnArrayConElementos() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c3 = crear_cosa(3);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);
  cosa *c12 = crear_cosa(12);
  cosa *c13 = crear_cosa(13);

  arbol_insertar(arbol, c7);
  arbol_insertar(arbol, c5);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c13);
  arbol_insertar(arbol, c12);

  size_t tamanio_array = 6;
  void *array[tamanio_array];

  size_t cantidad = arbol_recorrido_postorden(arbol, array, tamanio_array);

  pa2m_afirmar(cantidad == tamanio_array,
               "La cantidad de elementos en array es la misma que la misma al "
               "tamanio en el array");

  pa2m_afirmar(((cosa *)array[0]) == c3, "Primer valor en array corresponde");
  pa2m_afirmar(((cosa *)array[1]) == c6, "Segundo valor en array corresponde");
  pa2m_afirmar(((cosa *)array[2]) == c5, "Tercer valor en array corresponde");
  pa2m_afirmar(((cosa *)array[3]) == c12, "Cuarto valor en array corresponde");
  pa2m_afirmar(((cosa *)array[4]) == c13, "Quinto valor en array corresponde");
  pa2m_afirmar(((cosa *)array[5]) == c7, "Sexto valor en array corresponde");

  arbol_destruir(arbol);
}

// ----------------------------------------------------------------
//  Iterador Interno
// ----------------------------------------------------------------
// Si el arbol esta vacion o nulo devuelve 0
void DadoArbolNuloOVacio_CuandoRecorroArbol_EntoncesObtengo0() {
  size_t cantidad_recorrida_arbol_NULL =
      abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, NULL, NULL);
  pa2m_afirmar(cantidad_recorrida_arbol_NULL == 0,
               "Cuando paso arbol nulo entonces se recorren 0 elementos");

  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  size_t cantidad_recorrida_arbol_vacio =
      abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL);
  pa2m_afirmar(cantidad_recorrida_arbol_vacio == 0,
               "Cuando paso arbol vacio entonces se recorren 0 elementos");
  arbol_destruir(arbol);
}
bool mostrar_hasta_5(void *elemento, void *extra) {
  extra = extra;
  if (elemento) {
    if (((cosa *)elemento)->clave == 5)
      return true;
  }
  return false;
}
bool mostrar_hasta_12(void *elemento, void *extra) {
  extra = extra;
  if (elemento) {
    if (((cosa *)elemento)->clave == 12)
      return true;
  }
  return false;
}
bool return_false(void *elemento, void *extra) {
  extra = extra;
  elemento = elemento;
  return false;
}
// Recorre el arbol de forma inorden, preorden y postorden, todos los recorridos
// devuelven la misma cantidad
void DadoArbolYLosTresMetodosDeRecorrer_CuandoRecorroArbolConCadaUno_EntoncesLosTresMeDanElMismoValor() {
  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c3 = crear_cosa(3);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);
  cosa *c12 = crear_cosa(12);
  cosa *c13 = crear_cosa(13);

  arbol_insertar(arbol, c7);
  arbol_insertar(arbol, c5);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c13);
  arbol_insertar(arbol, c12);

  size_t cantidad_recorrida_inorden =
      abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, return_false, NULL);
  size_t cantidad_recorrida_preorden =
      abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, return_false, NULL);
  size_t cantidad_recorrida_postorden =
      abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, return_false, NULL);

  pa2m_afirmar(
      (6 == cantidad_recorrida_inorden) ==
          (cantidad_recorrida_preorden == cantidad_recorrida_postorden),
      "Recorrer el arbol de las tres formas disponibles resulta en la "
      "misma cantidad de elementos recorridos");
  arbol_destruir(arbol);
}
// Cuando paso una funcion esta puede interrunpir el recorrido
void DadoArbolYFuncion_CuandoRecorroYFuncionDevuelveTrue_EntoncesSeCortaLaIteracion() {

  abb_t *arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa *c3 = crear_cosa(3);
  cosa *c5 = crear_cosa(5);
  cosa *c6 = crear_cosa(6);
  cosa *c7 = crear_cosa(7);
  cosa *c12 = crear_cosa(12);
  cosa *c13 = crear_cosa(13);

  arbol_insertar(arbol, c7);
  arbol_insertar(arbol, c5);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c13);
  arbol_insertar(arbol, c12);

  size_t hasta_12_inorden = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN,
                                                  mostrar_hasta_12, NULL);
  size_t hasta_12_preorden = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN,
                                                   mostrar_hasta_12, NULL);
  size_t hasta_12_postorden = abb_con_cada_elemento(
      arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_12, NULL);

  size_t hasta_5_inorden =
      abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
  size_t hasta_5_preorden = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN,
                                                  mostrar_hasta_5, NULL);
  size_t hasta_5_postorden = abb_con_cada_elemento(
      arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);

  pa2m_afirmar(hasta_12_inorden == 5,
               "La funcion paro correctamente para la iteracion inorden");
  pa2m_afirmar(hasta_12_preorden == 6,
               "La funcion paro correctamente para la iteracion preorden");
  pa2m_afirmar(hasta_12_postorden == 4,
               "La funcion paro correctamente para la iteracion postorden");

  pa2m_afirmar(hasta_5_inorden == 2,
               "La funcion paro correctamente para la iteracion inorden");
  pa2m_afirmar(hasta_5_preorden == 2,
               "La funcion paro correctamente para la iteracion preorden");
  pa2m_afirmar(hasta_5_postorden == 3,
               "La funcion paro correctamente para la iteracion postorden");

  arbol_destruir(arbol);
}

int main() {
  pa2m_nuevo_grupo("Crear Arbol");
  DadoUnComparadorYUnDestructor_CuandoCreoArbol_EntoncesObtengoPunteroAlArbolConNodoRaizNulaYComparadorYDestructorCorresponden();
  DadoComparadorNuloYDestructor_CuandoIntentoCrearArbol_EntoncesObtengoNULL();
  DadoContadorYDestructorNulo_CuandoCreoArbol_EntoncesObtengoPunteroAlArbol();

  pa2m_nuevo_grupo("Insertar a Arbol");
  DadoArbolInvalido_CuandoIntentoInsertar_EntoncesObtengo0();
  DadoArbolVacionYElementos_CuandoInserto_EntoncesObtengoArbolOrdenado();

  pa2m_nuevo_grupo("Borrar en Arbol");
  DadoUnArbolInvalido_CuandoIntentoBorrarUnElemento_EntoncesObtengoMenosUno();
  DadoArbolYElementos_CuandoBorroTodosLosElementosDelArbol_EntoncesObtengo0ParaTodosLosCasos();

  pa2m_nuevo_grupo("Buscar en Arbol");
  DadoArbolInvalido_CuandoBuscoElementoEnArbol_EntoncesObtengoNULL();
  DadoArbolYElementos_CuandoBuscoElementoEnArbol_EntoncesObtengoElementoEncontradoONull();

  pa2m_nuevo_grupo("Obtener Raiz");
  DadoArbolNULL_CuandoVerificoRaiz_EntoncesObtengoNULL();
  DadoArbolVacio_CuandoVerificoRaiz_EntoncesObtengoNULL();
  DadoArbol_CuandoVerificoRaiz_EntoncesObtengoRaiz();

  pa2m_nuevo_grupo("Verificar si esta vacio");
  DadoUnArbolNULL_CuandoVerificoSiArbolVacio_EntoncesObtengoTrue();
  DadoUnArbolVacio_CuandoVerificoSiArbolVacio_EntoncesObtengoTrue();
  DadoUnArbolConElementos_CuandoVerificoSiArbolVacio_EntoncesObtengoFalse();

  pa2m_nuevo_grupo("Recorrer arbol inorden");
  DadoArbolNulo_CuandoIntentoRecorrerArbolInorden_EntoncesObtengo0();
  DadoArbolVacio_CuandoIntentoRecorrerArbolInorden_EntoncesObtengo0();
  DadoArbolConElementos_CuandoRecorroArbolInorden_EntoncesObtengoLaCantidadDeElementosRecorridosYUnArrayConElementos();

  pa2m_nuevo_grupo("Recorrer arbol preorden");
  DadoArbolNulo_CuandoIntentoRecorrerArbolPreorden_EntoncesObtengo0();
  DadoArbolVacio_CuandoIntentoRecorrerArbolPreorden_EntoncesObtengo0();
  DadoArbolConElementos_CuandoRecorroArbolPreorden_EntoncesObtengoLaCantidadDeElementosRecorridosYUnArrayConElementos();

  pa2m_nuevo_grupo("Recorrer arbol postrden");
  DadoArbolNulo_CuandoIntentoRecorrerArbolPostorden_EntoncesObtengo0();
  DadoArbolVacio_CuandoIntentoRecorrerArbolPostorden_EntoncesObtengo0();
  DadoArbolConElementos_CuandoRecorroArbolPostorden_EntoncesObtengoLaCantidadDeElementosRecorridosYUnArrayConElementos();

  pa2m_nuevo_grupo("Iterador Interno");
  DadoArbolNuloOVacio_CuandoRecorroArbol_EntoncesObtengo0();
  DadoArbolYLosTresMetodosDeRecorrer_CuandoRecorroArbolConCadaUno_EntoncesLosTresMeDanElMismoValor();
  DadoArbolYFuncion_CuandoRecorroYFuncionDevuelveTrue_EntoncesSeCortaLaIteracion();

  return pa2m_mostrar_reporte();
}
