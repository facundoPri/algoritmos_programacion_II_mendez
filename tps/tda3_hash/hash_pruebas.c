#include "hash.h"
#include "pa2mm.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define EXITO 0
#define ERROR -1

// Crear tabla hash
void DadaCapacidad_CuandoCreoTabla_EntoncesObtengoTablaHash() {
  hash_t *hash_0 = hash_crear(NULL, 0);
  pa2m_afirmar(hash_0, "Cuando paso un numero menor a 3 como capacidad inicial "
                       "se crea hash con capacidad incial = 3");

  hash_t *hash_10 = hash_crear(NULL, 10);
  pa2m_afirmar(hash_10, "Crear un hash sin pasar destructor es valido");

  hash_destruir(hash_0);
  hash_destruir(hash_10);
}

// Insertar elemento en hash
void DadosValoresInvalidos_CuandoIntentoInsertarElemento_EntoncesFuncionFalla() {
  hash_t *hash = hash_crear(NULL, 10);

  pa2m_afirmar(hash_insertar(NULL, "Test", (void *)5) == -1,
               "No se le puede insertar elemento a hash nulo");
  pa2m_afirmar(hash_insertar(hash, NULL, (void *)5) == -1,
               "No se le puede insertar elemento cuando clave es nula");
  hash_destruir(hash);
}

void DadosValoresValidos_CuandoInsertoElementos_EntoncesFuncionFunciona() {
  hash_t *hash = hash_crear(NULL, 10);

  pa2m_afirmar(hash_insertar(hash, "Primer", (void *)5) == 0,
               "Cuando inserto valor valido no ocurre error [1]");
  pa2m_afirmar(hash_cantidad(hash) == 1, "Hash contiene 1 elementos");
  pa2m_afirmar(hash_insertar(hash, "Segundo", (void *)5) == 0,
               "Cuando inserto valor valido no ocurre error [2]");
  pa2m_afirmar(hash_cantidad(hash) == 2, "Hash contiene 2 elementos");

  hash_destruir(hash);
}

void DadoMasValoresQueEl75PorCientoDeLaCapacidad_CuandoIntentoInsertarElementos_EntoncesFuncionFunciona() {
  hash_t *hash = hash_crear(NULL, 10);

  hash_insertar(hash, "1", (void *)5);
  hash_insertar(hash, "2", (void *)5);
  hash_insertar(hash, "3", (void *)5);
  hash_insertar(hash, "4", (void *)5);
  hash_insertar(hash, "5", (void *)5);
  hash_insertar(hash, "6", (void *)5);
  hash_insertar(hash, "7", (void *)5);
  pa2m_afirmar(hash_cantidad(hash) == 7, "Hash contiene 7 elementos");
  pa2m_afirmar(hash_insertar(hash, "8", (void *)5) == 0,
               "Insertar valores sigue funcionando [1]");
  pa2m_afirmar(hash_cantidad(hash) == 8, "Hash contiene 8 elementos");
  pa2m_afirmar(hash_insertar(hash, "9", (void *)5) == 0,
               "Insertar valores sigue funcionando [2]");
  pa2m_afirmar(hash_cantidad(hash) == 9, "Hash contiene 9 elementos");
  pa2m_afirmar(hash_insertar(hash, "10", (void *)5) == 0,
               "Insertar valores sigue funcionando [3]");
  pa2m_afirmar(hash_cantidad(hash) == 10, "Hash contiene 10 elementos");
  pa2m_afirmar(hash_insertar(hash, "11", (void *)5) == 0,
               "Insertar valores sigue funcionando [4]");
  pa2m_afirmar(hash_cantidad(hash) == 11, "Hash contiene 11 elementos");

  hash_destruir(hash);
}

void DadoElementoConClaveYaExistente_CuandoIntentoInsertarElemento_EntoncesFuncionFunciona() {
  hash_t *hash = hash_crear(NULL, 10);

  hash_insertar(hash, "1", (void *)5);
  hash_insertar(hash, "2", (void *)5);
  pa2m_afirmar(hash_cantidad(hash) == 2, "Hash contiene 2 elementos");
  pa2m_afirmar(hash_insertar(hash, "1", (void *)4) == 0,
               "Se inserto nuevo valor con misma clave [1]");
  pa2m_afirmar(hash_cantidad(hash) == 2,
               "Hash sigue conteniendo 2 elementos [1]");
  pa2m_afirmar(hash_insertar(hash, "2", (void *)4) == 0,
               "Se inserto nuevo valor con misma clave [2]");
  pa2m_afirmar(hash_cantidad(hash) == 2,
               "Hash sigue conteniendo 2 elementos [2]");

  hash_destruir(hash);
}

// Quitar Elemento
void DadoHashOClaveInvalidos_CuandoIntentoRemoverElmento_EntoncesFuncionFalla() {
  hash_t *hash_vacio = hash_crear(NULL, 10);
  hash_t *hash = hash_crear(NULL, 10);
  hash_insertar(hash, "1", (void *)5);
  hash_insertar(hash, "2", (void *)5);

  pa2m_afirmar(hash_quitar(NULL, "Clave") == ERROR,
               "No se puede quitar elemento a hash nulo");
  pa2m_afirmar(hash_quitar(hash_vacio, "Clave") == ERROR,
               "No se puede quitar elemento a hash vacio");
  pa2m_afirmar(hash_quitar(hash, "Clave") == ERROR,
               "No se puede quitar elemento que no pertenece al hash pasado");

  hash_destruir(hash_vacio);
  hash_destruir(hash);
}

void DadoHashValidoYClaveExistente_CuandoRemuevoElemento_EntoncesFuncionFunciona() {
  hash_t *hash = hash_crear(NULL, 10);
  hash_insertar(hash, "Colicionan", (void *)5);
  hash_insertar(hash, "nanoiciloC", (void *)5);
  hash_insertar(hash, "4", (void *)5);
  hash_insertar(hash, "5", (void *)5);
  hash_insertar(hash, "6", (void *)5);
  hash_insertar(hash, "7", (void *)5);

  pa2m_afirmar(hash_cantidad(hash) == 6, "Hash contiene 6 elementos");
  pa2m_afirmar(hash_quitar(hash, "Colicionan") == EXITO,
               "Se puede remover [1]");
  pa2m_afirmar(hash_cantidad(hash) == 5, "Hash contiene 5 elementos");
  pa2m_afirmar(hash_quitar(hash, "4") == EXITO, "Se puede remover [2]");
  pa2m_afirmar(hash_cantidad(hash) == 4, "Hash contiene 4 elementos");
  pa2m_afirmar(hash_quitar(hash, "nanoiciloC") == EXITO,
               "Se puede remover [3]");
  pa2m_afirmar(hash_cantidad(hash) == 3, "Hash contiene 3 elementos");
  pa2m_afirmar(hash_quitar(hash, "5") == EXITO, "Se puede remover [4]");
  pa2m_afirmar(hash_cantidad(hash) == 2, "Hash contiene 2 elementos");
  pa2m_afirmar(hash_quitar(hash, "7") == EXITO, "Se puede remover [5]");
  pa2m_afirmar(hash_cantidad(hash) == 1, "Hash contiene 1 elementos");
  pa2m_afirmar(hash_quitar(hash, "6") == EXITO, "Se puede remover [6]");
  pa2m_afirmar(hash_cantidad(hash) == 0, "Hash contiene 0 elementos");

  pa2m_afirmar(hash_obtener(hash, "Colicionan") == NULL,
               "Elemento eliminado no fue encontrado [1]");
  pa2m_afirmar(hash_obtener(hash, "nanoiciloC") == NULL,
               "Elemento eliminado no fue encontrado [2]");
  pa2m_afirmar(hash_obtener(hash, "4") == NULL,
               "Elemento eliminado no fue encontrado [3]");
  pa2m_afirmar(hash_obtener(hash, "5") == NULL,
               "Elemento eliminado no fue encontrado [4]");
  pa2m_afirmar(hash_obtener(hash, "6") == NULL,
               "Elemento eliminado no fue encontrado [5]");
  pa2m_afirmar(hash_obtener(hash, "7") == NULL,
               "Elemento eliminado no fue encontrado [6]");
  hash_destruir(hash);
}

// Obtener elemento
void DadoHashOClaveInvalida_CuandoBuscoElemento_EntoncesObtengUnError() {
  hash_t *hash_vacio = hash_crear(NULL, 10);
  hash_t *hash = hash_crear(NULL, 10);
  hash_insertar(hash, "1", (void *)5);
  hash_insertar(hash, "2", (void *)5);

  pa2m_afirmar(hash_obtener(NULL, "Clave") == NULL,
               "Hash nulo no tiene el elemento buscado");
  pa2m_afirmar(hash_obtener(hash_vacio, "Clave") == NULL,
               "Hash vacio no contiene el elemento buscado");
  pa2m_afirmar(hash_obtener(hash, "Clave") == NULL,
               "Clave pasada no esta almacenada en el hash");

  hash_destruir(hash);
  hash_destruir(hash_vacio);
}

void DadoHashYClavesAlmacenadaEnHash_CuandoBuscoElemento_EntoncesObtengoElElementoDeseado() {
  hash_t *hash = hash_crear(NULL, 10);

  hash_insertar(hash, "1", (void *)1);
  hash_insertar(hash, "2", (void *)2);
  hash_insertar(hash, "3", (void *)3);
  hash_insertar(hash, "4", (void *)4);
  hash_insertar(hash, "5", (void *)5);
  hash_insertar(hash, "6", (void *)6);
  hash_insertar(hash, "7", (void *)7);

  pa2m_afirmar(hash_obtener(hash, "1") == (void *)1,
               "Se ha encontrado el elemento buscado[1]");
  pa2m_afirmar(hash_obtener(hash, "2") == (void *)2,
               "Se ha encontrado el elemento buscado[2]");
  pa2m_afirmar(hash_obtener(hash, "3") == (void *)3,
               "Se ha encontrado el elemento buscado[3]");
  pa2m_afirmar(hash_obtener(hash, "4") == (void *)4,
               "Se ha encontrado el elemento buscado[4]");
  pa2m_afirmar(hash_obtener(hash, "5") == (void *)5,
               "Se ha encontrado el elemento buscado[5]");
  pa2m_afirmar(hash_obtener(hash, "6") == (void *)6,
               "Se ha encontrado el elemento buscado[6]");
  pa2m_afirmar(hash_obtener(hash, "7") == (void *)7,
               "Se ha encontrado el elemento buscado[7]");

  hash_destruir(hash);
}

// Contiene elemento
void DadoHashOClaveInvalida_CuandoBuscoSiElementoEstaContenido_EntoncesObtengFalse() {
  hash_t *hash_vacio = hash_crear(NULL, 10);
  hash_t *hash = hash_crear(NULL, 10);
  hash_insertar(hash, "1", (void *)5);
  hash_insertar(hash, "2", (void *)5);

  pa2m_afirmar(hash_contiene(NULL, "Clave") == false,
               "Hash nulo no tiene el elemento buscado");
  pa2m_afirmar(hash_contiene(hash_vacio, "Clave") == false,
               "Hash vacio no contiene el elemento buscado");
  pa2m_afirmar(hash_contiene(hash, "Clave") == false,
               "Clave pasada no esta almacenada en el hash");

  hash_destruir(hash);
  hash_destruir(hash_vacio);
}

void DadoHashYClavesAlmacenadaEnHash_CuandoBuscoSiElementoEstaContenido_EntoncesObtengoTrue() {
  hash_t *hash = hash_crear(NULL, 10);

  hash_insertar(hash, "1", (void *)1);
  hash_insertar(hash, "2", (void *)2);
  hash_insertar(hash, "3", (void *)3);
  hash_insertar(hash, "4", (void *)4);
  hash_insertar(hash, "5", (void *)5);
  hash_insertar(hash, "6", (void *)6);
  hash_insertar(hash, "7", (void *)7);

  pa2m_afirmar(hash_contiene(hash, "1") == true, "Hash contiene elemento[1]");
  pa2m_afirmar(hash_contiene(hash, "2") == true, "Hash contiene elemento[2]");
  pa2m_afirmar(hash_contiene(hash, "3") == true, "Hash contiene elemento[3]");
  pa2m_afirmar(hash_contiene(hash, "4") == true, "Hash contiene elemento[4]");
  pa2m_afirmar(hash_contiene(hash, "5") == true, "Hash contiene elemento[5]");
  pa2m_afirmar(hash_contiene(hash, "6") == true, "Hash contiene elemento[6]");
  pa2m_afirmar(hash_contiene(hash, "7") == true, "Hash contiene elemento[7]");

  hash_destruir(hash);
}

// Iteracion
void DadoHashNULLOVacio_CuandoIntentoIterar_EntoncesObtengo0() {
  hash_t *hash = hash_crear(NULL, 10);

  pa2m_afirmar(hash_con_cada_clave(NULL, NULL, NULL) == 0,
               "No se puede iterar un hash Nulo");
  pa2m_afirmar(hash_con_cada_clave(hash, NULL, NULL) == 0,
               "Iterar un hash vacio devuelve 0");

  hash_destruir(hash);
}

bool mostrar_par(hash_t *hash, const char *clave, void *aux) {
  if (!clave)
    return true;
  aux = aux;

  char *elemento = hash_obtener(hash, clave);

  printf("Clave: %s, Elemento: %s\n", clave, elemento);

  return false;
}

bool recorrer_hasta_clave(hash_t *hash, const char *clave, void *ultima_clave) {
  if (!clave)
    return true;

  if (strcmp(clave, ultima_clave) == 0) {
    return true;
  }

  return false;
}

void DadoHashCon10Elementos_CuandoIteroLos10_EntoncesObtengo10() {
  hash_t *hash = hash_crear(NULL, 10);

  hash_insertar(hash, "1", (void *)1);
  hash_insertar(hash, "2", (void *)2);
  hash_insertar(hash, "3", (void *)3);
  hash_insertar(hash, "4", (void *)4);
  hash_insertar(hash, "5", (void *)5);
  hash_insertar(hash, "6", (void *)6);
  hash_insertar(hash, "7", (void *)7);
  hash_insertar(hash, "8", (void *)8);
  hash_insertar(hash, "9", (void *)9);
  hash_insertar(hash, "10", (void *)10);

  size_t cantidad_iterada = hash_con_cada_clave(hash, NULL, NULL);
  pa2m_afirmar(
      cantidad_iterada == 10,
      "Cuando no paso funcion se itera la cantidad de elementos en el hash");

  // hash_con_cada_clave(hash, mostrar_par, NULL);

  cantidad_iterada = hash_con_cada_clave(hash, recorrer_hasta_clave, "5");
  pa2m_afirmar(
      cantidad_iterada == 5,
      "Cuando paso funcion se itera hasta que la funcion devuelve true");

  hash_destruir(hash);
}

int main() {
  pa2m_nuevo_grupo("Crear Tabla");
  DadaCapacidad_CuandoCreoTabla_EntoncesObtengoTablaHash();

  pa2m_nuevo_grupo("Insertar Elemento");
  DadosValoresInvalidos_CuandoIntentoInsertarElemento_EntoncesFuncionFalla();
  DadosValoresValidos_CuandoInsertoElementos_EntoncesFuncionFunciona();
  DadoMasValoresQueEl75PorCientoDeLaCapacidad_CuandoIntentoInsertarElementos_EntoncesFuncionFunciona();
  DadoElementoConClaveYaExistente_CuandoIntentoInsertarElemento_EntoncesFuncionFunciona();

  pa2m_nuevo_grupo("Quitar Elemento");
  DadoHashOClaveInvalidos_CuandoIntentoRemoverElmento_EntoncesFuncionFalla();
  DadoHashValidoYClaveExistente_CuandoRemuevoElemento_EntoncesFuncionFunciona();

  pa2m_nuevo_grupo("Obtener elemento");
  DadoHashOClaveInvalida_CuandoBuscoElemento_EntoncesObtengUnError();
  DadoHashYClavesAlmacenadaEnHash_CuandoBuscoElemento_EntoncesObtengoElElementoDeseado();

  pa2m_nuevo_grupo("Contiene elemento");
  DadoHashOClaveInvalida_CuandoBuscoSiElementoEstaContenido_EntoncesObtengFalse();
  DadoHashYClavesAlmacenadaEnHash_CuandoBuscoSiElementoEstaContenido_EntoncesObtengoTrue();

  pa2m_nuevo_grupo("Iterador");
  DadoHashNULLOVacio_CuandoIntentoIterar_EntoncesObtengo0();
  DadoHashCon10Elementos_CuandoIteroLos10_EntoncesObtengo10();

  return pa2m_mostrar_reporte();
}
