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
  arbol_insertar(arbol, c2);
  pa2m_afirmar(
      arbol->nodo_raiz->izquierda->derecha->elemento == c2,
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

int main() {
  pa2m_nuevo_grupo("Crear Arbol");
  DadoUnComparadorYUnDestructor_CuandoCreoArbol_EntoncesObtengoPunteroAlArbolConNodoRaizNulaYComparadorYDestructorCorresponden();
  DadoComparadorNuloYDestructor_CuandoIntentoCrearArbol_EntoncesObtengoNULL();
  DadoContadorYDestructorNulo_CuandoCreoArbol_EntoncesObtengoPunteroAlArbol();

  pa2m_nuevo_grupo("Insertar a Arbol");
  DadoArbolInvalido_CuandoIntentoInsertar_EntoncesObtengo0();
  DadoArbolVacionYElementos_CuandoInserto_EntoncesObtengoArbolOrdenado();
  return pa2m_mostrar_reporte();
}
