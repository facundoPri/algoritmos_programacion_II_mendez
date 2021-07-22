#include "entrenador.h"
#include "abb.h"
#include "hash.h"
#include "lista.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _pokemon_t {
  const char *nombre;
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
  free(pokemon);
}

entrenador_t *entrenador_crear(const char *nombre, int victorias) {
  if (!nombre)
    return NO_EXISTE;
  entrenador_t *entrenador = calloc(1, sizeof(entrenador_t));
  if (!entrenador)
    return NO_EXISTE;

  entrenador->nombre = nombre;
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

  nuevo_pokemon->nombre = nombre;
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

int comparador_metodo_clasico(void *pokemon1, void *pokemon2) {
  pokemon_t *p1 = pokemon1;
  pokemon_t *p2 = pokemon2;
  int coeficiente_pokemon1 =
      8 * (p1->nivel) + 10 * (p1->fuerza) + 20 * (p1->velocidad);
  int coeficiente_pokemon2 =
      8 * (p2->nivel) + 10 * (p2->fuerza) + 20 * (p2->velocidad);
  return coeficiente_pokemon1 - coeficiente_pokemon2;
}

int comparador_metodo_moderno(void *pokemon1, void *pokemon2) {
  pokemon_t *p1 = pokemon1;
  pokemon_t *p2 = pokemon2;
  int coeficiente_pokemon1 =
      5 * (p1->nivel) + 9 * (p1->defensa) + 30 * (p1->inteligencia);
  int coeficiente_pokemon2 =
      5 * (p2->nivel) + 9 * (p2->defensa) + 30 * (p2->inteligencia);
  return coeficiente_pokemon1 - coeficiente_pokemon2;
}

bool insertar_abb_desde_hash(hash_t *hash, const char *clave, void *abb) {
  pokemon_t *pokemon = hash_obtener(hash, clave);
  int resultado = arbol_insertar((abb_t *)abb, pokemon);
  if (resultado == ERROR)
    return true;
  return false;
}

lista_t *entrenador_lista_ordenada_pokemones(entrenador_t *entrenador,
                                             int metodo_ordenamiento,
                                             size_t cantidad) {
  if (!entrenador || (metodo_ordenamiento != METODO_CLASICO &&
                      metodo_ordenamiento != METODO_MODERNO))
    return NO_EXISTE;
  if (cantidad == 0) {
    cantidad = entrenador_cantidad_pokemones(entrenador);
  }

  abb_t *arbol_pokemones;
  if (metodo_ordenamiento == METODO_CLASICO) {
    arbol_pokemones = arbol_crear(comparador_metodo_clasico, NULL);
  } else if (metodo_ordenamiento == METODO_MODERNO) {
    arbol_pokemones = arbol_crear(comparador_metodo_moderno, NULL);
  } else
    return NO_EXISTE;

  size_t cantidad_arbol = hash_con_cada_clave(
      entrenador->pokemones, insertar_abb_desde_hash, arbol_pokemones);
  if (cantidad_arbol != entrenador_cantidad_pokemones(entrenador)) {
    arbol_destruir(arbol_pokemones);
    return NO_EXISTE;
  }

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
  hash_destruir(entrenador->pokemones);
  free(entrenador);
};