#include "salon.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

salon_t *salon_leer_archivo(const char *nombre_archivo) {
  FILE *archivo = fopen(nombre_archivo, "r");
  if (!archivo)
    return NULL;

  char *linea = NULL;
  entrenador_t **entrenadores = NULL;
  salon_t *salon = calloc(1, sizeof(salon_t));

  while ((linea = fgets_alloc(archivo))) {
    char **elementos_linea = split(linea, ';');
    size_t len = vtrlen(elementos_linea);
    if (len == 2) {
      entrenador_t *entrenador = calloc(1, sizeof(entrenador_t));
      entrenadores = vtradd(entrenadores, entrenador);
      salon->entrenadores = entrenadores;
      strcpy(entrenador->nombre, elementos_linea[0]);
      entrenador->victorias = atoi(elementos_linea[1]);
      pokemon_t **equipo = NULL;
      entrenador->equipo = equipo;
    } else if (len == 6) {
      pokemon_t *pokemon = malloc(1*sizeof(pokemon_t));
      strcpy(pokemon->nombre, elementos_linea[0]);
      pokemon->nivel = atoi(elementos_linea[1]);
      pokemon->defensa = atoi(elementos_linea[2]);
      pokemon->fuerza = atoi(elementos_linea[3]);
      pokemon->inteligencia = atoi(elementos_linea[4]);
      pokemon->velocidad = atoi(elementos_linea[5]);
      salon->entrenadores[vtrlen(entrenadores) - 1]->equipo = vtradd(
          salon->entrenadores[vtrlen(entrenadores) - 1]->equipo, pokemon);
    }
  }
  fclosen(archivo);
  return salon;
}

int salon_guardar_archivo(salon_t *salon, const char *nombre_archivo) {

  FILE* archivo = fopen(nombre_archivo,"w");

  if(!archivo){
   fclosen(archivo); 
    return -1;
  }
  int i;
  for (i = 0; i < vtrlen(salon->entrenadores); i++) {
    fprintf(archivo,"%s;%i\n", salon->entrenadores[i]->nombre, salon->entrenadores[i]->victorias);
    for(int n =0; n< vtrlen(salon->entrenadores[i]->equipo); n++){
      fprintf(archivo,"%s;%i;%i;%i;%i;%i\n", salon->entrenadores[i]->equipo[n]->nombre,salon->entrenadores[i]->equipo[n]->nivel,salon->entrenadores[i]->equipo[n]->defensa,salon->entrenadores[i]->equipo[n]->fuerza,salon->entrenadores[i]->equipo[n]->inteligencia,salon->entrenadores[i]->equipo[n]->velocidad);
    }
  }

  fclosen(archivo);
  return i;
}

salon_t *salon_agregar_entrenador(salon_t *salon, entrenador_t *entrenador) {

  if (!salon || !entrenador) {
    return NULL;
  }
  entrenador_t **entrenadores_ordenados = NULL;
  //TODO: Chequer por que no entra el ultimo y lo tengo que poner aparte en un if
  for (int i = 0; i < vtrlen(salon->entrenadores); i++) {
    if (entrenador->victorias < salon->entrenadores[i]->victorias &&
        vtrlen(entrenadores_ordenados) == i) {
      entrenadores_ordenados = vtradd(entrenadores_ordenados, entrenador);
    }
    entrenadores_ordenados =
        vtradd(entrenadores_ordenados, salon->entrenadores[i]);
  }
  if (vtrlen(entrenadores_ordenados) == vtrlen(salon->entrenadores)) {
    entrenadores_ordenados = vtradd(entrenadores_ordenados, entrenador);
  }

  salon->entrenadores = entrenadores_ordenados;

  return salon;
}

entrenador_t **salon_obtener_entrenadores_mas_ganadores(salon_t *salon, int cantidad_minima_victorias) {
  entrenador_t ** encontrados = NULL;
  for (int i = 0; i < vtrlen(salon->entrenadores); i++) {
    if(salon->entrenadores[i]->victorias>=cantidad_minima_victorias){
      encontrados= vtradd(encontrados,salon->entrenadores[i]);
    }
  }

  return encontrados;
}

void salon_mostrar_entrenador(entrenador_t *entrenador) {
  printf("Entrenador: %s\nVictorias: %i\n\n", entrenador->nombre, entrenador->victorias);

}

void salon_destruir(salon_t *salon) {
  
}


//TODO: Caso de error devolver NULL, chequear en todas las funciones