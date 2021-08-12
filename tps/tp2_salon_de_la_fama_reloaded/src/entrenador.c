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
  size_t ultimoId;
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
  fprintf(archivo, "%s;%i;%i;%i;%i;%i\n", p->nombre, p->nivel, p->defensa, p->fuerza,
          p->inteligencia, p->velocidad);
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
  entrenador->ultimoId = 0;
  entrenador->pokemones = hash_crear(destruir_pokemon, 10);
  if (!entrenador->pokemones) {
    free(entrenador);
    return NO_EXISTE;
  }

  return entrenador;
};

int entrenador_insertar_pokemon(entrenador_t *entrenador, const char *nombre,
                                int nivel, int defensa, int fuerza, int inteligencia,
                                int velocidad) {
  if (!entrenador || !nombre)
    return ERROR;

  pokemon_t *nuevo_pokemon = calloc(1, sizeof(pokemon_t));
  if (!nuevo_pokemon)
    return ERROR;


  nuevo_pokemon->orden = entrenador->ultimoId;
  nuevo_pokemon->nombre = duplicar_str(nombre);
  nuevo_pokemon->nivel = nivel;
  nuevo_pokemon->defensa = defensa;
  nuevo_pokemon->fuerza = fuerza;
  nuevo_pokemon->inteligencia = inteligencia;
  nuevo_pokemon->velocidad = velocidad;
  entrenador->ultimoId++;
  int resultado = hash_insertar(entrenador->pokemones, nombre, nuevo_pokemon);
  if (resultado == ERROR) {
    free(nuevo_pokemon);
    return ERROR;
  }
  printf("Nuevo Pokemon de %s: %s,%i,%i,%i,%i,%i, id:%zu\n",
         entrenador->nombre,
         nombre,
         nivel,
         defensa,
         fuerza,
         inteligencia,
         velocidad,
         entrenador->ultimoId);

  return EXITO;
};

int entrenador_quitar_pokemon(entrenador_t *entrenador, const char *nombre) {
  if (!entrenador || !nombre || entrenador_cantidad_pokemones(entrenador) <= 1)
    return ERROR;
  printf("Pokemon borrar: %s\n", nombre);
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
  printf("pokemon->orden %lu\n",pokemon->orden);
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

  printf("hash a abb\n");
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
    int resultado = lista_encolar(lista_pokemones, array_pokemones[i]);
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
int entrenador_victorias(entrenador_t *entrenador) {
  if (!entrenador)
    return -1;
  return entrenador->victorias;
}

/*
** Recibe un entrenador y devuelve su nombre
*/
const char *entrenador_nombre(entrenador_t *entrenador) {
  if (!entrenador)
    return NULL;
  return entrenador->nombre;
}

hash_t *entrenador_pokemon_a_hash(pokemon_t *pokemon) {
  if (!pokemon)
    return NO_EXISTE;
  hash_t *pokemon_hash = hash_crear(NO_EXISTE, 10);
  if (!pokemon_hash)
    return NO_EXISTE;

  hash_insertar(pokemon_hash, "nombre", (void *)pokemon->nombre);
  hash_insertar(pokemon_hash, "nivel", (void *)&pokemon->nivel);
  hash_insertar(pokemon_hash, "defensa", (void *)&pokemon->defensa);
  hash_insertar(pokemon_hash, "fuerza", (void *)&pokemon->fuerza);
  hash_insertar(pokemon_hash, "inteligencia", (void *)&pokemon->inteligencia);
  hash_insertar(pokemon_hash, "velocidad", (void *)&pokemon->velocidad);
  hash_insertar(pokemon_hash, "orden", (void *)&pokemon->orden);

  return pokemon_hash;
}

/*
** Recibe un entrenador y el nombre de su pokemon, devuelve un hash con los
*atributos del pokemon o NULL en caso de error
*/
hash_t *entrenador_pokemon_atributos(entrenador_t *entrenador,
                                     const char *nombre_pokemon) {
  if (!entrenador)
    return NO_EXISTE;
  pokemon_t *pokemon = entrenador_buscar_pokemon(entrenador, nombre_pokemon);
  if (!pokemon)
    return NO_EXISTE;
  hash_t *pokemon_hash = entrenador_pokemon_a_hash(pokemon);

  return pokemon_hash;
}
