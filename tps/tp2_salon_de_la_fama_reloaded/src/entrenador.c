#include "entrenador.h"
#include "abb.h"
#include "hash.h"
#include "lista.h"
#include "util.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _pokemon_t {
  const char *nombre;
  size_t orden;
  int nivel;
  int fuerza;
  int inteligencia;
  int velocidad;
  int defensa;
};

struct _entrenador_t {
  const char *nombre;
  int victorias;
  hash_t *pokemones;
};

/**
 * Funcion utilizada para liberar la memoria al eliminar un elemento en el hash.
 * Recibe un elemento void y libera la memoria utilizada por el.
 */
void destruir_pokemon(void *pokemon) {
  if (!pokemon)
    return;
  free((void *)((pokemon_t *)pokemon)->nombre);
  free(pokemon);
}

/**
 * Funcion recibe un pokemon y un archivo, y lo anota. Si hubo un error
 * devuelve true, si no devuelve false.
 */
bool guardar_pokemon_archivo(void *pokemon, void *archivo) {
  if (!pokemon || !archivo)
    return false;
  pokemon_t *p = pokemon;
  fprintf(archivo, "%s;%i;%i;%i;%i;%i\n", p->nombre, p->nivel, p->defensa,
          p->fuerza, p->inteligencia, p->velocidad);
  return true;
}

bool guardar_entrenador_archivo(void *entrenador, void *archivo) {
  if (!entrenador || !archivo)
    return true;

  entrenador_t *e = entrenador;
  fprintf(archivo, "%s;%i\n", e->nombre, e->victorias);
  lista_t *lista_pokemones = entrenador_lista_ordenada_pokemones(entrenador, 0);
  lista_con_cada_elemento(lista_pokemones, guardar_pokemon_archivo, archivo);
  lista_destruir(lista_pokemones);

  return false;
}

entrenador_t *entrenador_crear(const char *nombre, int victorias) {
  if (!nombre)
    return NO_EXISTE;
  entrenador_t *entrenador = calloc(1, sizeof(entrenador_t));
  if (!entrenador)
    return NO_EXISTE;

  entrenador->nombre = duplicar_str(nombre);
  entrenador->victorias = victorias;
  entrenador->pokemones = hash_crear(destruir_pokemon, 10);
  if (!entrenador->pokemones) {
    free(entrenador);
    return NO_EXISTE;
  }

  return entrenador;
};

int entrenador_insertar_pokemon(entrenador_t *entrenador, const char *nombre,
                                int nivel, int fuerza, int inteligencia,
                                int velocidad, int defensa) {
  if (!entrenador || !nombre)
    return ERROR;

  pokemon_t *nuevo_pokemon = calloc(1, sizeof(pokemon_t));
  if (!nuevo_pokemon)
    return ERROR;

  nuevo_pokemon->orden = hash_cantidad(entrenador->pokemones) + 1;
  nuevo_pokemon->nombre = duplicar_str(nombre);
  nuevo_pokemon->nivel = nivel;
  nuevo_pokemon->fuerza = fuerza;
  nuevo_pokemon->inteligencia = inteligencia;
  nuevo_pokemon->velocidad = velocidad;
  nuevo_pokemon->defensa = defensa;

  int resultado = hash_insertar(entrenador->pokemones, nombre, nuevo_pokemon);
  if (resultado == ERROR) {
    free(nuevo_pokemon);
    return ERROR;
  }

  return EXITO;
};

int entrenador_quitar_pokemon(entrenador_t *entrenador, const char *nombre) {
  if (!entrenador || !nombre || entrenador_cantidad_pokemones(entrenador) <= 1)
    return ERROR;
  int resultado = hash_quitar(entrenador->pokemones, nombre);
  return resultado;
};

int entrenador_comparador(entrenador_t *entrenador1,
                          entrenador_t *entrenador2) {
  if (!entrenador1 || !entrenador2) {
    return ERROR;
  }
  return strcmp(entrenador1->nombre, entrenador2->nombre);
};

size_t entrenador_cantidad_pokemones(entrenador_t *entrenador) {
  if (!entrenador)
    return 0;

  return hash_cantidad(entrenador->pokemones);
};

pokemon_t *entrenador_buscar_pokemon(entrenador_t *entrenador,
                                     const char *nombre_pokemon) {
  if (!entrenador || !nombre_pokemon)
    return NO_EXISTE;

  return hash_obtener(entrenador->pokemones, nombre_pokemon);
};

int comparador_por_orden(void *pokemon1, void *pokemon2) {
  pokemon_t *p1 = pokemon1;
  pokemon_t *p2 = pokemon2;
  return (int)p1->orden - (int)p2->orden;
}
// TODO documentar funciones auxiliares
bool insertar_abb_desde_hash(hash_t *hash, const char *clave, void *abb) {
  pokemon_t *pokemon = hash_obtener(hash, clave);
  int resultado = arbol_insertar((abb_t *)abb, pokemon);
  if (resultado == ERROR)
    return true;
  return false;
}

lista_t *entrenador_lista_ordenada_pokemones(entrenador_t *entrenador,
                                             size_t cantidad) {
  if (!entrenador)
    return NO_EXISTE;
  if (cantidad == 0) {
    cantidad = entrenador_cantidad_pokemones(entrenador);
  }

  abb_t *arbol_pokemones;
  arbol_pokemones = arbol_crear(comparador_por_orden, NULL);

  size_t cantidad_arbol = hash_con_cada_clave(
      entrenador->pokemones, insertar_abb_desde_hash, arbol_pokemones);

  if (cantidad_arbol != entrenador_cantidad_pokemones(entrenador)) {
    arbol_destruir(arbol_pokemones);
    return NO_EXISTE;
  }

  // TODO: Usar tda lista
  pokemon_t **array_pokemones[cantidad];
  size_t cantidad_recorrida = arbol_recorrido_inorden(
      arbol_pokemones, (void **)array_pokemones, cantidad);

  if (cantidad_recorrida != cantidad &&
      cantidad_recorrida != entrenador_cantidad_pokemones(entrenador)) {
    arbol_destruir(arbol_pokemones);
    return NO_EXISTE;
  }

  arbol_destruir(arbol_pokemones);
  lista_t *lista_pokemones = lista_crear();
  if (!lista_pokemones)
    return NO_EXISTE;

  for (int i = 0; i < cantidad; i++) {
    int resultado = lista_apilar(lista_pokemones, array_pokemones[i]);
    if (resultado == ERROR) {
      lista_destruir(lista_pokemones);
      return NO_EXISTE;
    }
  }

  return lista_pokemones;
};

void entrenador_destruir(entrenador_t *entrenador) {
  if (!entrenador)
    return;
  free((void *)entrenador->nombre);
  hash_destruir(entrenador->pokemones);
  free(entrenador);
};

/*
** Recibe un entrenador y devuelve la cantidad de victorias
*/
int entrenador_victorias(entrenador_t*entrenador){
  if (!entrenador)return -1;
  return entrenador->victorias;
}

/*
** Recibe un entrenador y devuelve su nombre
*/
const char * entrenador_nombre(entrenador_t*entrenador){
  if (!entrenador)return NULL;
  return entrenador->nombre;
}
