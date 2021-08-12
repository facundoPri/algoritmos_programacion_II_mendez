#ifndef ENTRENADOR_H_
#define ENTRENADOR_H_

#include "abb.h"
#include "hash.h"
#include "lista.h"
#include "util.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define METODO_CLASICO 1
#define METODO_MODERNO 2

#define NO_EXISTE NULL
#define ERROR -1
#define EXITO 0

typedef struct _entrenador_t entrenador_t;
typedef struct _pokemon_t pokemon_t;

/**
 * Recibe una string con el nombre del entrenador y la cantidad de victorias,
 * crea el entrenador y devuelve un puntero a el. En caso de error devuelve NULL
 */
entrenador_t *entrenador_crear(const char *nombre, int victorias);

/**
 * Recibe el nombre, nivel, fuerza, inteligencia y defensa del pokemon y el
 * entrenador a quien se le va a agregar, devuelve 0 es caso de exito o -1 en
 * caso de error;
 */
int entrenador_insertar_pokemon(entrenador_t *entrenador, const char *nombre,
                                int nivel, int fuerza, int inteligencia,
                                int velocidad, int defensa);

/**
 * Recibe un entrenador y el nombre del pokemon que se desea eliminar, devuelve
 * 0 en caso de exito -1 en caso de error.
 */
int entrenador_quitar_pokemon(entrenador_t *entrenador, const char *nombre);

/**
 * Funcion utilizada para comparar dos entrenadores, los compara de forma
 * alfabetica.
 * Si entrenador1 > entrenador2 => >0
 * Si entrenador1 = entrenador2 => 0
 * Si entrenador1 < entrenador2 => <0
 */
int entrenador_comparador(entrenador_t *entrenador1, entrenador_t *entrenador2);

/**
 * Funcion recibe un entrenador y un archivo, y lo anota. Si hubo un error
 * devuelve true, si no devuelve false.
 */
bool guardar_entrenador_archivo(void *entrenador, void *archivo);

/**
 * Recibe entrenador y devuelve la cantidad de pokemones que contiene.
 * Devuelve 0 encaso de error.
 */
size_t entrenador_cantidad_pokemones(entrenador_t *entrenador);

/**
 * Recibe un entrenador y el nombre del pokemon buscado. Devuelve el pokemon
 * buscado o NULL, en caso de no encontrarlo.
 */
pokemon_t *entrenador_buscar_pokemon(entrenador_t *entrenador,
                                     const char *nombre_pokemon);

/**
 * Recibe un entrenador y la cantidad de pokemones deseados. Devuelve una lista
 * ordenada con la cantidad de pokemones deseados. Si no se pasa la cantidad o
 * es 0 se almacenan todos los pokemones.
 */
lista_t *entrenador_lista_ordenada_pokemones(entrenador_t *entrenador,
                                             size_t cantidad);

/**
 * Recibe un entrenador y libera la memoria utilizada.
 */
void entrenador_destruir(entrenador_t *entrenador);

/**
 * Recibe un entrenador y devuelve la cantidad de victorias
 */
int entrenador_victorias(entrenador_t *entrenador);

/**
 * Recibe un entrenador y devuelve su nombre
 */
const char *entrenador_nombre(entrenador_t *entrenador);

/*
** Recibe un pokemon y devuelve sus atributos en un hash, caso de error devuelve
*NULL
*/
hash_t *entrenador_pokemon_a_hash(pokemon_t *pokemon);

/*
** Recibe un entrenador y el nombre de su pokemon, devuelve un hash con los
*atributos del pokemon o NULL en caso de error
*/
hash_t *entrenador_pokemon_atributos(entrenador_t *entrenador,
                                     const char *nombre_pokemon);
#endif // ENTRENADOR_H_
