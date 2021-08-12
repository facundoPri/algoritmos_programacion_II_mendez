#include "salon.h"
#include "abb.h"
#include "entrenador.h"
#include "hash.h"
#include "lista.h"
#include "util.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// Defines

#define ENTRENADOR 2
#define POKEMON 6

// Estructuras

static hash_t *comandos_hash = NULL;
static hash_t *reglas_hash = NULL;

typedef char *(*comando_ejecutar_t)(const char *, salon_t *);

typedef int (*comparador_pokemon)(pokemon_t *, pokemon_t *);

typedef struct regla {
  char *nombre;
  char *descripcion;
  comparador_pokemon comparador;
} regla_t;

struct _salon_t {
  abb_t *entrenadores;
};

// Funciones auxiliares

int comparador_entrenadores_abb(void *entrenador1, void *entrenador2) {
  return entrenador_comparador((entrenador_t *)entrenador1,
                               (entrenador_t *)entrenador2);
}

void destructor_entrenador_abb(void *entrenador) {
  entrenador_destruir((entrenador_t *)entrenador);
}

entrenador_t *salon_buscar_entrenador(salon_t *salon,
                                      const char *entrenador_nombre) {
  if (!salon || !salon->entrenadores)
    return NULL;

  entrenador_t *entrenador_aux = entrenador_crear(entrenador_nombre, 0);
  entrenador_t *entrenador = arbol_buscar(salon->entrenadores, entrenador_aux);

  entrenador_destruir(entrenador_aux);
  return entrenador;
}

/*
 * Recibe la lista con elementos en linea y devuelve un entrenador creado con
 * esa informacion. Devuelve NULL en caso de error.
 */
entrenador_t *crear_entrenador_con_lista(lista_t *lista_info) {
  if (!lista_info)
    return NO_EXISTE;
  char *nombre = lista_elemento_en_posicion(lista_info, 0);
  int victorias = atoi(lista_elemento_en_posicion(lista_info, 1));
  if (victorias == 0)
    return NO_EXISTE;
  return entrenador_crear(nombre, victorias);
}

/*
 * Recibe la lista con elementos en linea, el entrenador que contiene al pokemon
 * y la cantidad de pokemones que contiene. Devuelve -1 en caso de un error, 0
 * en caso de exito.
 */
int insertar_pokemon_con_lista(lista_t *lista_info, entrenador_t *entrenador,
                               size_t *cantidad_pokemones) {
  if (!lista_info || !entrenador || !cantidad_pokemones)
    return ERROR;
  char *nombre = lista_elemento_en_posicion(lista_info, 0);
  int nivel = atoi(lista_elemento_en_posicion(lista_info, 1));
  if (nivel == 0)
    return ERROR;
  int defensa = atoi(lista_elemento_en_posicion(lista_info, 2));
  if (defensa == 0)
    return ERROR;
  int fuerza = atoi(lista_elemento_en_posicion(lista_info, 3));
  if (fuerza == 0)
    return ERROR;
  int inteligencia = atoi(lista_elemento_en_posicion(lista_info, 4));
  if (inteligencia == 0)
    return ERROR;
  int velocidad = atoi(lista_elemento_en_posicion(lista_info, 5));
  if (velocidad == 0)
    return ERROR;
  int resultado = entrenador_insertar_pokemon(
      entrenador, nombre, nivel, defensa, fuerza, inteligencia, velocidad);
  (*cantidad_pokemones)++;
  return resultado;
}

// TODO pensar mejor esta funcion
// TODO pensar esto con la funcion lista_con_cada_elemento
/*
 * Recibe un salon y un archivo. Devuelve 0 si pudo almacenar los datos del
 * archivo en el salon o -1 si no.
 */
int pasar_archivo_a_salon(salon_t *salon, FILE *archivo) {
  if (!salon || !archivo)
    return ERROR;

  lista_t *archivo_salon_lista = csv_reader(archivo, ';');
  if (!archivo_salon_lista || lista_elementos(archivo_salon_lista) == 0) {
    destruir_csv_lista(archivo_salon_lista);
    return ERROR;
  }

  lista_iterador_t *iterador_archivo_csv;

  entrenador_t *entrenador_actual = NULL;
  size_t cantidad_pokemones = 0;

  for (iterador_archivo_csv = lista_iterador_crear(archivo_salon_lista);
       lista_iterador_tiene_siguiente(iterador_archivo_csv);
       lista_iterador_avanzar(iterador_archivo_csv)) {
    lista_t *linea_actual =
        lista_iterador_elemento_actual(iterador_archivo_csv);
    size_t cantidad_elementos = lista_elementos(linea_actual);
    if (cantidad_elementos == ENTRENADOR) {
      if (entrenador_actual) {
        if (cantidad_pokemones == 0) {
          destruir_csv_lista(archivo_salon_lista);
          lista_iterador_destruir(iterador_archivo_csv);
          return ERROR;
        }
      }
      entrenador_actual = crear_entrenador_con_lista(linea_actual);
      if (!entrenador_actual ||
          salon_buscar_entrenador(salon,
                                  entrenador_nombre(entrenador_actual))) {
        if (entrenador_actual)
          entrenador_destruir(entrenador_actual);
        destruir_csv_lista(archivo_salon_lista);
        lista_iterador_destruir(iterador_archivo_csv);
        return ERROR;
      }
      arbol_insertar(salon->entrenadores, entrenador_actual);
      cantidad_pokemones = 0;
    } else if (cantidad_elementos == POKEMON) {
      int resultado = insertar_pokemon_con_lista(
          linea_actual, entrenador_actual, &cantidad_pokemones);
      if (resultado == ERROR) {
        destruir_csv_lista(archivo_salon_lista);
        lista_iterador_destruir(iterador_archivo_csv);
        return ERROR;
      }
    } else {
      // ERROR
      destruir_csv_lista(archivo_salon_lista);
      lista_iterador_destruir(iterador_archivo_csv);
      return ERROR;
    }
  }

  if (entrenador_actual) {
    if (cantidad_pokemones == 0) {
      destruir_csv_lista(archivo_salon_lista);
      lista_iterador_destruir(iterador_archivo_csv);
      return ERROR;
    }
  }

  destruir_csv_lista(archivo_salon_lista);
  lista_iterador_destruir(iterador_archivo_csv);
  return EXITO;
}

/*
** Si la string pasada es un numero devuelve true, caso contrario false
*/
bool string_es_numero(char *num) {
  for (int i = 0; i < strlen(num); i++) {
    if (!isdigit(num[i])) {
      return false;
    }
  }
  return true;
}

bool entrenador_tiene_victorias(entrenador_t *entrenador, void *victorias) {
  if (!entrenador || !victorias)
    return false;
  if (entrenador_victorias(entrenador) >= atoi(victorias))
    return true;
  return false;
}

bool entrenador_tiene_pokemon(entrenador_t *entrenador, void *pokemon) {
  if (!entrenador || !pokemon)
    return false;
  if (entrenador_buscar_pokemon(entrenador, pokemon))
    return true;
  return false;
}

char *juntar_entrenadores(lista_t *entrenadores, bool mostrar_victorias) {
  if (!entrenadores)
    return NULL;
  char *string_final = calloc(1000, 1);
  strcpy(string_final, "");

  if (!string_final)
    return NULL;

  lista_iterador_t *iterador_lista_entrenadores;

  for (iterador_lista_entrenadores = lista_iterador_crear(entrenadores);
       lista_iterador_tiene_siguiente(iterador_lista_entrenadores);
       lista_iterador_avanzar(iterador_lista_entrenadores)) {

    entrenador_t *entrenador =
        lista_iterador_elemento_actual(iterador_lista_entrenadores);

    char entrenador_string[100];
    int resultado;
    if (mostrar_victorias) {
      resultado =
          sprintf(entrenador_string, "%s,%i\n", entrenador_nombre(entrenador),
                  entrenador_victorias(entrenador));
    } else {
      resultado =
          sprintf(entrenador_string, "%s\n", entrenador_nombre(entrenador));
    }

    if (resultado < 0) {
      free(string_final);
      lista_iterador_destruir(iterador_lista_entrenadores);
    }

    if (string_final)
      strcat(string_final, entrenador_string);
  }
  lista_iterador_destruir(iterador_lista_entrenadores);
  return string_final;
}

char *ejecutar_comando_entrenador(const char *parametros, salon_t *salon) {
  if (!salon)
    return NULL;
  lista_t *parametros_elementos = split(parametros, ',');
  if (lista_elementos(parametros_elementos)>2){
    destruir_lista_split(parametros_elementos);
    return NULL;
  }
  char *primer_parametro = lista_elemento_en_posicion(parametros_elementos, 0);
  char *segundo_parametro = lista_elemento_en_posicion(parametros_elementos, 1);
  lista_t *entrenadores = NULL;
  char *string_final = NULL;

  if (!primer_parametro && !segundo_parametro) {
    entrenadores = salon_filtrar_entrenadores(salon, NULL, NULL);
  } else if (strcmp(primer_parametro, "victorias") == 0 && segundo_parametro &&
             isdigit(*segundo_parametro) > 0) {
    entrenadores = salon_filtrar_entrenadores(salon, entrenador_tiene_victorias,
                                              segundo_parametro);
  } else if (strcmp(primer_parametro, "pokemon") == 0 && segundo_parametro) {
    entrenadores = salon_filtrar_entrenadores(salon, entrenador_tiene_pokemon,
                                              segundo_parametro);
  } else {
    lista_destruir(entrenadores);
    destruir_lista_split(parametros_elementos);
    return NULL;
  }

  if (!primer_parametro && !segundo_parametro) {
    string_final = juntar_entrenadores(entrenadores, true);
  } else {
    string_final = juntar_entrenadores(entrenadores, false);
  }

  lista_destruir(entrenadores);
  destruir_lista_split(parametros_elementos);
  return string_final;
}

char *juntar_pokemones(lista_t *pokemones) {
  if (!pokemones)
    return NULL;
  char *string_final = calloc(1000, 1);
  if (!string_final)
    return NULL;

  lista_iterador_t *iterador_lista_pokemones;
  hash_t *hash_pokemon = NULL;

  for (iterador_lista_pokemones = lista_iterador_crear(pokemones);
       lista_iterador_tiene_siguiente(iterador_lista_pokemones);
       lista_iterador_avanzar(iterador_lista_pokemones)) {

    pokemon_t *pokemon =
        lista_iterador_elemento_actual(iterador_lista_pokemones);

    hash_t *hash_pokemon = entrenador_pokemon_a_hash(pokemon);
    char pokemon_string[100];
    int resultado = sprintf(pokemon_string, "%s,%i,%i,%i,%i,%i\n",
                            (char *)hash_obtener(hash_pokemon, "nombre"),
                            *(int *)hash_obtener(hash_pokemon, "nivel"),
                            *(int *)hash_obtener(hash_pokemon, "defensa"),
                            *(int *)hash_obtener(hash_pokemon, "fuerza"),
                            *(int *)hash_obtener(hash_pokemon, "inteligencia"),
                            *(int *)hash_obtener(hash_pokemon, "velocidad"));
    if (resultado < 0) {
      free(string_final);
      hash_destruir(hash_pokemon);
      lista_iterador_destruir(iterador_lista_pokemones);
    }

    if (string_final)
      strcat(string_final, pokemon_string);
    hash_destruir(hash_pokemon);
  }

  if (hash_pokemon)
    hash_destruir(hash_pokemon);
  lista_iterador_destruir(iterador_lista_pokemones);
  return string_final;
}

char *ejecutar_comando_equipo(const char *parametros, salon_t *salon) {
  if (!salon)
    return NULL;

  lista_t *parametros_elementos = split(parametros, ',');
  char *nombre = lista_elemento_en_posicion(parametros_elementos, 0);
  char *string_final = NULL;
  entrenador_t *entrenador = salon_buscar_entrenador(salon, nombre);

  lista_t *pokemones = NULL;

  if (entrenador) {
    pokemones = entrenador_lista_ordenada_pokemones(entrenador, 0);
  }

  if (pokemones) {
    string_final = juntar_pokemones(pokemones);
  }
  lista_destruir(pokemones);
  destruir_lista_split(parametros_elementos);
  return string_final;
}

bool hash_reglas_a_lista(hash_t *hash, const char *clave, void *lista) {
  int resultado = lista_insertar(lista, hash_obtener(hash, clave));
  if (resultado == -1) {
    return true;
  }
  return false;
}
char *juntar_reglas(lista_t *reglas) {
  if (!reglas)
    return NULL;
  char *string_final = calloc(1000, 1);
  if (!string_final)
    return NULL;

  lista_iterador_t *iterador_lista_reglas;

  for (iterador_lista_reglas = lista_iterador_crear(reglas);
       lista_iterador_tiene_siguiente(iterador_lista_reglas);
       lista_iterador_avanzar(iterador_lista_reglas)) {

    regla_t *regla = lista_iterador_elemento_actual(iterador_lista_reglas);

    strcat(string_final, regla->nombre);
    strcat(string_final, ",");
    strcat(string_final, regla->descripcion);
    strcat(string_final, "\n");
  }

  lista_iterador_destruir(iterador_lista_reglas);
  return string_final;
}

char *ejecutar_comando_reglas(const char *parametro, salon_t *salon) {
  if (parametro)
    return NULL;
  salon = salon;
  if (hash_cantidad(reglas_hash) == 0)
    return NO_EXISTE;
  char *string_final = NULL;

  lista_t *lista_reglas = lista_crear();
  size_t cantidad =
      hash_con_cada_clave(reglas_hash, hash_reglas_a_lista, lista_reglas);

  if (cantidad != hash_cantidad(reglas_hash)) {
    lista_destruir(lista_reglas);
    return NO_EXISTE;
  }
  string_final = juntar_reglas(lista_reglas);

  lista_destruir(lista_reglas);
  return string_final;
}

char *ejecutar_comando_comparar(const char *parametros, salon_t *salon) {
  if (!salon)
    return NO_EXISTE;
  lista_t *parametros_elementos = split(parametros, ',');
  char *tercer_parametro = lista_elemento_en_posicion(parametros_elementos, 2);
  if (lista_elementos(parametros_elementos) != 3 ||
      !hash_obtener(reglas_hash, tercer_parametro)) {
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }

  char *primer_parametro = lista_elemento_en_posicion(parametros_elementos, 0);
  char *segundo_parametro = lista_elemento_en_posicion(parametros_elementos, 1);

  char *string_final = calloc(1000, 1);
  if (!string_final) {
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }

  entrenador_t *entrenador1 = salon_buscar_entrenador(salon, primer_parametro);
  entrenador_t *entrenador2 = salon_buscar_entrenador(salon, segundo_parametro);
  if (!entrenador1 || !entrenador2) {
    free(string_final);
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }

  lista_t *lista_pokemones_entrenador1 =
      entrenador_lista_ordenada_pokemones(entrenador1, 0);
  lista_t *lista_pokemones_entrenador2 =
      entrenador_lista_ordenada_pokemones(entrenador2, 0);

  regla_t *regla = hash_obtener(reglas_hash, tercer_parametro);
  pokemon_t *pokemon1_actual = lista_tope(lista_pokemones_entrenador1);
  pokemon_t *pokemon2_actual = lista_tope(lista_pokemones_entrenador2);
  while (pokemon1_actual && pokemon2_actual) {

    int resultado = regla->comparador(pokemon1_actual, pokemon2_actual);
    char resultado_string[10];
    sprintf(resultado_string, "%i\n", resultado);
    strcat(string_final, resultado_string);
    if (resultado == 1) {
      lista_desapilar(lista_pokemones_entrenador2);
    } else {
      lista_desapilar(lista_pokemones_entrenador1);
    }
    pokemon1_actual = lista_tope(lista_pokemones_entrenador1);
    pokemon2_actual = lista_tope(lista_pokemones_entrenador2);
  }

  lista_destruir(lista_pokemones_entrenador1);
  lista_destruir(lista_pokemones_entrenador2);
  destruir_lista_split(parametros_elementos);
  return string_final;
}

char *ejecutar_comando_agregar_pokemon(const char *parametros, salon_t *salon) {
  if (!salon)
    return NO_EXISTE;
  lista_t *parametros_elementos = split(parametros, ',');
  if (lista_elementos(parametros_elementos) < 7) {
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }

  char *nombre_entrenador = lista_elemento_en_posicion(parametros_elementos, 0);
  char *nombre_pokemon = lista_elemento_en_posicion(parametros_elementos, 1);
  char *nivel = lista_elemento_en_posicion(parametros_elementos, 2);
  char *defensa = lista_elemento_en_posicion(parametros_elementos, 3);
  char *fuerza = lista_elemento_en_posicion(parametros_elementos, 4);
  char *inteligencia = lista_elemento_en_posicion(parametros_elementos, 5);
  char *velocidad = lista_elemento_en_posicion(parametros_elementos, 6);

  if (isdigit(*nivel) == 0 || isdigit(*defensa) == 0 || isdigit(*fuerza) == 0 ||
      isdigit(*inteligencia) == 0 || isdigit(*velocidad) == 0) {
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }
  entrenador_t *entrenador = salon_buscar_entrenador(salon, nombre_entrenador);
  if (!entrenador) {
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }
  int resultado = entrenador_insertar_pokemon(
      entrenador, nombre_pokemon, atoi(nivel), atoi(defensa), atoi(fuerza),
      atoi(inteligencia), atoi(velocidad));
  destruir_lista_split(parametros_elementos);
  if (resultado == -1)
    return NO_EXISTE;
  return duplicar_str("OK");
}

char *ejecutar_comando_quitar_pokemon(const char *parametros, salon_t *salon) {
  if (!salon)
    return NO_EXISTE;
  lista_t *parametros_elementos = split(parametros, ',');
  if (lista_elementos(parametros_elementos) != 2) {
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }

  char *nombre_entrenador = lista_elemento_en_posicion(parametros_elementos, 0);
  char *nombre_pokemon = lista_elemento_en_posicion(parametros_elementos, 1);

  entrenador_t *entrenador = salon_buscar_entrenador(salon, nombre_entrenador);
  if (!entrenador) {
    destruir_lista_split(parametros_elementos);
    return NO_EXISTE;
  }
  int resultado = entrenador_quitar_pokemon(entrenador, nombre_pokemon);

  destruir_lista_split(parametros_elementos);
  if (resultado == -1)
    return NO_EXISTE;
  return duplicar_str("OK");
}

char *ejecutar_comando_guardar(const char *nombre_archivo, salon_t *salon) {
  if (!salon || !*nombre_archivo)
    return NO_EXISTE;

  int resultado = salon_guardar_archivo(salon, nombre_archivo);

  if (resultado == -1)
    return NO_EXISTE;
  return duplicar_str("OK");
}

/*
** Recibe el hash comandos globas y lo inicializa si este no existe
*/
int inicializar_comandos(hash_t *comandos) {
  if (comandos)
    return 0;
  comandos_hash = hash_crear(NULL, 10);
  if (!comandos_hash)
    return -1;
  hash_insertar(comandos_hash, "ENTRENADORES", ejecutar_comando_entrenador);
  hash_insertar(comandos_hash, "EQUIPO", ejecutar_comando_equipo);
  hash_insertar(comandos_hash, "REGLAS", ejecutar_comando_reglas);
  hash_insertar(comandos_hash, "COMPARAR", ejecutar_comando_comparar);
  hash_insertar(comandos_hash, "AGREGAR_POKEMON",
                ejecutar_comando_agregar_pokemon);
  hash_insertar(comandos_hash, "QUITAR_POKEMON",
                ejecutar_comando_quitar_pokemon);
  hash_insertar(comandos_hash, "GUARDAR", ejecutar_comando_guardar);

  return 0;
}

/*
** Recibe dos pokemones, devuelve 1 si gano el primer pokemon y 2 si gano el
*segundo
*/
int comparador_clasico(pokemon_t *pokemon1, pokemon_t *pokemon2) {
  hash_t *hash_pokemon1 = entrenador_pokemon_a_hash(pokemon1);
  hash_t *hash_pokemon2 = entrenador_pokemon_a_hash(pokemon2);

  double coeficiente_de_batalla_pokemon1 =
      (0.8 * (*(int *)hash_obtener(hash_pokemon1, "nivel")) +
       (*(int *)hash_obtener(hash_pokemon1, "fuerza")) +
       2 * (*(int *)hash_obtener(hash_pokemon1, "velocidad")));

  double coeficiente_de_batalla_pokemon2 =
      (0.8 * (*(int *)hash_obtener(hash_pokemon2, "nivel")) +
       (*(int *)hash_obtener(hash_pokemon2, "fuerza")) +
       2 * (*(int *)hash_obtener(hash_pokemon2, "velocidad")));

  hash_destruir(hash_pokemon1);
  hash_destruir(hash_pokemon2);
  if (coeficiente_de_batalla_pokemon1 >= coeficiente_de_batalla_pokemon2) {
    return 1;
  } else {
    return 2;
  }
}
/*
** Recibe dos pokemones, devuelve 1 si gano el primer pokemon y 2 si gano el
*segundo
*/
int comparador_moderno(pokemon_t *pokemon1, pokemon_t *pokemon2) {
  hash_t *hash_pokemon1 = entrenador_pokemon_a_hash(pokemon1);
  hash_t *hash_pokemon2 = entrenador_pokemon_a_hash(pokemon2);

  double coeficiente_de_batalla_pokemon1 =
      (0.5 * (*(int *)hash_obtener(hash_pokemon1, "nivel")) +
       0.9 * (*(int *)hash_obtener(hash_pokemon1, "defensa")) +
       3 * (*(int *)hash_obtener(hash_pokemon1, "inteligencia")));

  double coeficiente_de_batalla_pokemon2 =
      (0.5 * (*(int *)hash_obtener(hash_pokemon2, "nivel")) +
       0.9 * (*(int *)hash_obtener(hash_pokemon2, "defensa")) +
       3 * (*(int *)hash_obtener(hash_pokemon2, "inteligencia")));

  hash_destruir(hash_pokemon1);
  hash_destruir(hash_pokemon2);
  if (coeficiente_de_batalla_pokemon1 >= coeficiente_de_batalla_pokemon2) {
    return 1;
  } else {
    return 2;
  }
}
/*
** Recibe dos pokemones, devuelve 1 si gano el primer pokemon y 2 si gano el
*segundo
*/
int comparador_estratega(pokemon_t *pokemon1, pokemon_t *pokemon2) {
  hash_t *hash_pokemon1 = entrenador_pokemon_a_hash(pokemon1);
  hash_t *hash_pokemon2 = entrenador_pokemon_a_hash(pokemon2);

  int coeficiente_de_batalla_pokemon1 =
      (*(int *)hash_obtener(hash_pokemon1, "inteligencia"));

  int coeficiente_de_batalla_pokemon2 =
      (*(int *)hash_obtener(hash_pokemon2, "inteligencia"));

  hash_destruir(hash_pokemon1);
  hash_destruir(hash_pokemon2);
  if (coeficiente_de_batalla_pokemon1 >= coeficiente_de_batalla_pokemon2) {
    return 1;
  } else {
    return 2;
  }
}
/*
** Recibe dos pokemones, devuelve 1 si gano el primer pokemon y 2 si gano el
*segundo
*/
int comparador_mayor_nombre(pokemon_t *pokemon1, pokemon_t *pokemon2) {
  hash_t *hash_pokemon1 = entrenador_pokemon_a_hash(pokemon1);
  hash_t *hash_pokemon2 = entrenador_pokemon_a_hash(pokemon2);

  size_t coeficiente_de_batalla_pokemon1 =
      strlen(hash_obtener(hash_pokemon1, "nombre"));

  size_t coeficiente_de_batalla_pokemon2 =
      strlen(hash_obtener(hash_pokemon2, "nombre"));

  hash_destruir(hash_pokemon1);
  hash_destruir(hash_pokemon2);
  if (coeficiente_de_batalla_pokemon1 >= coeficiente_de_batalla_pokemon2) {
    return 1;
  } else {
    return 2;
  }
}
/*
** Recibe dos pokemones, devuelve 1 si gano el primer pokemon y 2 si gano el
*segundo
*/
int comparador_fuerza_bruta(pokemon_t *pokemon1, pokemon_t *pokemon2) {
  hash_t *hash_pokemon1 = entrenador_pokemon_a_hash(pokemon1);
  hash_t *hash_pokemon2 = entrenador_pokemon_a_hash(pokemon2);

  int coeficiente_de_batalla_pokemon1 =
      (*(int *)hash_obtener(hash_pokemon1, "fuerza"));

  int coeficiente_de_batalla_pokemon2 =
      (*(int *)hash_obtener(hash_pokemon2, "fuerza"));

  hash_destruir(hash_pokemon1);
  hash_destruir(hash_pokemon2);
  if (coeficiente_de_batalla_pokemon1 >= coeficiente_de_batalla_pokemon2) {
    return 1;
  } else {
    return 2;
  }
}

/*
** Recibe el hash reglas globas y lo inicializa si este no existe
*/
int inicializar_reglas(hash_t *reglas) {
  if (reglas)
    return 0;

  reglas_hash = hash_crear(NULL, 10);
  if (!reglas_hash)
    return -1;
  regla_t *regla_clasico = calloc(1, sizeof(regla_t));
  regla_clasico->nombre = "CLASICO";
  regla_clasico->descripcion = "Aplica esta formula (0,8*nivel + fuerza + "
                               "2*velocidad) para calcular el pokemon ganador";
  regla_clasico->comparador = comparador_clasico;
  regla_t *regla_moderno = calloc(1, sizeof(regla_t));
  regla_moderno->nombre = "MODERNO";
  regla_moderno->descripcion =
      "Aplica esta formula (0,5*nivel + 0,9*defensa + 3*inteligencia) para "
      "calcular el pokemon ganador";
  regla_moderno->comparador = comparador_moderno;
  regla_t *regla_estratega = calloc(1, sizeof(regla_t));
  regla_estratega->nombre = "ESTRATEGA";
  regla_estratega->descripcion = "Gana el pokemon mas inteligente";
  regla_estratega->comparador = comparador_estratega;
  regla_t *regla_mayor_nombre = calloc(1, sizeof(regla_t));
  regla_mayor_nombre->nombre = "MAYOR_NOMBRE";
  regla_mayor_nombre->descripcion = "Gana el pokemon con mayor nombre";
  regla_mayor_nombre->comparador = comparador_mayor_nombre;
  regla_t *regla_fuerza_bruta = calloc(1, sizeof(regla_t));
  regla_fuerza_bruta->nombre = "FUERZA_BRUTA";
  regla_fuerza_bruta->descripcion = "Gana el pokemon mas fuerte";
  regla_fuerza_bruta->comparador = comparador_fuerza_bruta;

  hash_insertar(reglas_hash, "CLASICO", regla_clasico);
  hash_insertar(reglas_hash, "MODERNO", regla_moderno);
  hash_insertar(reglas_hash, "ESTRATEGA", regla_estratega);
  hash_insertar(reglas_hash, "MAYOR_NOMBRE", regla_mayor_nombre);
  hash_insertar(reglas_hash, "FUERZA_BRUTA", regla_fuerza_bruta);

  return 0;
}

salon_t *salon_leer_archivo(const char *nombre_archivo) {
  if (!nombre_archivo)
    return NO_EXISTE;
  if (comandos_hash == NULL)
    inicializar_comandos(comandos_hash);
  if (reglas_hash == NULL)
    inicializar_reglas(reglas_hash);

  FILE *archivo = fopen(nombre_archivo, "r");
  if (!archivo)
    return NO_EXISTE;

  salon_t *salon = calloc(1, sizeof(salon_t));
  if (salon == NO_EXISTE) {
    fclosen(archivo);
    return NO_EXISTE;
  }
  salon->entrenadores =
      arbol_crear(comparador_entrenadores_abb, destructor_entrenador_abb);
  if (salon->entrenadores == NO_EXISTE) {
    salon_destruir(salon);
    fclosen(archivo);
    return NO_EXISTE;
  }

  int resultado = pasar_archivo_a_salon(salon, archivo);
  if (resultado == ERROR) {
    salon_destruir(salon);
    fclosen(archivo);
    return NO_EXISTE;
  }

  fclosen(archivo);
  return salon;
}

int salon_guardar_archivo(salon_t *salon, const char *nombre_archivo) {
  if (!salon)
    return -1;
  // Abre el archivo donde se guardara el salon
  FILE *archivo = fopen(nombre_archivo, "w");
  if (!archivo) {
    fclosen(archivo);
    return -1;
  }

  size_t cantidad =
      abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN,
                            guardar_entrenador_archivo, archivo);

  fclosen(archivo);
  return (int)cantidad;
}

salon_t *salon_agregar_entrenador(salon_t *salon, entrenador_t *entrenador) {
  if (!salon || !entrenador || entrenador_cantidad_pokemones(entrenador) == 0)
    return NULL;

  if (arbol_buscar(salon->entrenadores, entrenador))
    return NULL;
  arbol_insertar(salon->entrenadores, entrenador);

  return salon;
}

bool retornar_siempre_false(entrenador_t *entrenador, void *extra) {
  entrenador = entrenador;
  extra = extra;
  return false;
}

bool agregar_entrenador_lista(void *entrenador, void *lista) {
  lista_insertar(lista, entrenador);
  return false;
}

lista_t *salon_filtrar_entrenadores(salon_t *salon,
                                    bool (*f)(entrenador_t *, void *),
                                    void *extra) {
  if (!salon)
    return NULL;
  lista_t *lista_entrenadores = lista_crear();
  if (!lista_entrenadores)
    return NULL;
  abb_con_cada_elemento(salon->entrenadores, ABB_RECORRER_INORDEN,
                        agregar_entrenador_lista, lista_entrenadores);

  if (!f)
    return lista_entrenadores;

  lista_t *lista_entrenadores_final = lista_crear();
  if (!lista_entrenadores_final) {
    lista_destruir(lista_entrenadores);
    return NULL;
  }

  lista_iterador_t *iterador_lista_entrenadores;
  bool agregar = true;

  for (iterador_lista_entrenadores = lista_iterador_crear(lista_entrenadores);
       lista_iterador_tiene_siguiente(iterador_lista_entrenadores);
       lista_iterador_avanzar(iterador_lista_entrenadores)) {
    entrenador_t *entrenador =
        lista_iterador_elemento_actual(iterador_lista_entrenadores);
    if (f)
      agregar = f(entrenador, extra);
    if (agregar) {
      lista_encolar(lista_entrenadores_final, entrenador);
    }
  }

  lista_destruir(lista_entrenadores);
  lista_iterador_destruir(iterador_lista_entrenadores);
  return lista_entrenadores_final;
}

// TODO implementar join
// TODO Implementar reglas
char *salon_ejecutar_comando(salon_t *salon, const char *comando) {
  if (!salon || !comando || !*comando)
    return NULL;
  // Separar comando con split
  lista_t *comando_elementos = split(comando, ':');

  comando_ejecutar_t comando_ejecutar =
      hash_obtener(comandos_hash, lista_tope(comando_elementos));
  if (!comando_ejecutar) {
    destruir_lista_split(comando_elementos);
    return NULL;
  }

  char *resultado =
      comando_ejecutar(lista_elemento_en_posicion(comando_elementos, 1), salon);

  destruir_lista_split(comando_elementos);
  return resultado;
}

void salon_destruir(salon_t *salon) {
  if (!salon)
    return;
  if (salon->entrenadores)
    arbol_destruir(salon->entrenadores);
  free(salon);
}
