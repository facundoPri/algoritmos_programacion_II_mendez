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

#define ENTRENADOR 2
#define POKEMON 6

static hash_t *comandos_hash = NULL;
static hash_t *reglas_hash = NULL;

typedef char *(*comando_ejecutar_t)(const char *, salon_t *);

/* typedef struct comando { */
/*   const char *nombre; */
/*   comando_ejecutar_t ejecutar; */
/* } comando_t; */

struct _salon_t {
  abb_t *entrenadores;
};

int comparador_entrenadores_abb(void *entrenador1, void *entrenador2) {
  return entrenador_comparador((entrenador_t *)entrenador1,
                               (entrenador_t *)entrenador2);
}

void destructor_entrenador_abb(void *entrenador) {
  entrenador_destruir((entrenador_t *)entrenador);
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
  int fuerza = atoi(lista_elemento_en_posicion(lista_info, 2));
  if (fuerza == 0)
    return ERROR;
  int inteligencia = atoi(lista_elemento_en_posicion(lista_info, 3));
  if (inteligencia == 0)
    return ERROR;
  int velocidad = atoi(lista_elemento_en_posicion(lista_info, 4));
  if (velocidad == 0)
    return ERROR;
  int defensa = atoi(lista_elemento_en_posicion(lista_info, 5));
  if (defensa == 0)
    return ERROR;
  int resultado = entrenador_insertar_pokemon(entrenador, nombre, nivel, fuerza,
                                              inteligencia, velocidad, defensa);
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
      if (!entrenador_actual) {
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
  printf("%s\n", entrenador_nombre(entrenador));
  if (entrenador_victorias(entrenador) >= atoi(victorias))
    return true;
  return false;
}

bool entrenador_tiene_pokemon(entrenador_t *entrenador, void *pokemon) {
  if (!entrenador || !pokemon)
    return false;
  if (entrenador_tiene_pokemon(entrenador, pokemon))
    return true;
  return false;
}

bool print_listas(void *elemento, void *contexto) {
  contexto = contexto;
  printf("%s\n", (char *)elemento);

  return true;
}
bool formatear_entrenador_con_victorias(void *entrenador, void *string) {
  if (!entrenador || !string)
    return false;
  char *entrenador_string = malloc(500);
  if (!entrenador_string)
    return false;
  int resultado =
      sprintf(entrenador_string, "%s,%i\n", entrenador_nombre(entrenador),
              entrenador_victorias(entrenador));
  if (resultado > 0)
    return false;
  strcat(string, entrenador_string);
  /* sprintf(string, "%s%s", (char *)string, entrenador_string); */
  free(entrenador_string);
  return true;
}
bool formatear_entrenador_sin_victorias(void *entrenador, void *string) {
  if (!entrenador || !string)
    return false;
  char *entrenador_string = malloc(500);
  if (!entrenador_string)
    return false;
  int resultado =
      sprintf(entrenador_string, "%s\n", entrenador_nombre(entrenador));
  if (resultado > 0)
    return false;
  strcat(string, entrenador_string);
  /* sprintf(string, "%s%s", (char *)string, entrenador_string); */
  free(entrenador_string);
  return true;
}

char *juntar_entrenadores(lista_t *entrenadores, bool mostrar_victorias) {
  if (!entrenadores)
    return NULL;
  char *string_final = malloc(5000);
  if (!string_final)
    return NULL;
  if (mostrar_victorias)
    lista_con_cada_elemento(entrenadores, formatear_entrenador_con_victorias,
                            string_final);
  else
    lista_con_cada_elemento(entrenadores, formatear_entrenador_sin_victorias,
                            string_final);
  return string_final;
}

char *ejecutar_comando_entrenador(const char *parametros, salon_t *salon) {
  if (!salon)
    return NULL;
  lista_t *parametros_elementos = split(parametros, ',');
  char *primer_parametro = lista_elemento_en_posicion(parametros_elementos, 0);
  char *segundo_parametro = lista_elemento_en_posicion(parametros_elementos, 1);
  lista_t *entrenadores = NULL;
  char *string_final = NULL;

  if (!primer_parametro && !segundo_parametro) {
    printf("ENTRENADORES");
    entrenadores = salon_filtrar_entrenadores(salon, NULL, NULL);
  } else if (strcmp(primer_parametro, "victorias") == 0 && segundo_parametro &&
             atoi(segundo_parametro) > 0) {
    printf("ENTRENADORES:victorias");
    entrenadores = salon_filtrar_entrenadores(salon, entrenador_tiene_victorias,
                                              segundo_parametro);
  } else if (strcmp(primer_parametro, "pokemon") == 0 && segundo_parametro) {
    printf("ENTRENADORES:pokemon");
    entrenadores = salon_filtrar_entrenadores(salon, entrenador_tiene_pokemon,
                                              segundo_parametro);
  }

  if (entrenadores) {
    if (!primer_parametro && !segundo_parametro) {
      /* lista_con_cada_elemento(entrenadores, print_listas, NULL); */
      string_final = juntar_entrenadores(entrenadores, true);
    } else {
      string_final = juntar_entrenadores(entrenadores, false);
    }
  }

  destruir_lista_split(parametros_elementos);
  return string_final;
}

int agregar_comando(hash_t *hash, const char *nombre,
                    comando_ejecutar_t funcion) {
  if (!hash || !nombre || !funcion)
    return -1;
  return hash_insertar(comandos_hash, nombre, funcion);
}

// TODO Crear inicializadores
/*
** Recibe el hash comandos globas y lo inicializa si este no existe
*/
int inicializar_comandos(hash_t *comandos) {
  if (comandos)
    return 0;
  comandos_hash = hash_crear(NULL, 10);
  agregar_comando(comandos_hash, "ENTRENADORES", ejecutar_comando_entrenador);

  return 0;
}
/*
** Recibe el hash reglas globas y lo inicializa si este no existe
*/
int inicializar_reglas(hash_t *reglas) {
  if (reglas)
    return 0;
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
// TODO Implementar hash con comandos
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

  comando_ejecutar(lista_elemento_en_posicion(comando_elementos, 1), salon);

  destruir_lista_split(comando_elementos);
  return NULL;
}

void salon_destruir(salon_t *salon) {
  if (!salon)
    return;
  if (salon->entrenadores)
    arbol_destruir(salon->entrenadores);
  free(salon);
}
