#include "pa2mm.h"
#include "src/entrenador.h"
#include "src/lista.h"
#include "src/salon.h"
#include "src/util.h"
#include "tdas/tda_hash/hash.h"
#include <stdio.h>
#include <string.h>

// Entrenador crear
void DadoNombreNULL_CuandoIntentoCrearEntrenador_EntoncesObtengoNULL() {
  entrenador_t *entrenador = entrenador_crear(NULL, 1);
  pa2m_afirmar(entrenador == NO_EXISTE,
               "Si paso NULL como nombre no se podra crear un entrenador");
}
void DadoNombreValido_CuandoCreoEntrenador_EntoncesNoObtengoNULL() {
  entrenador_t *entrenador = entrenador_crear("entrenador1", 1);
  pa2m_afirmar(entrenador != NO_EXISTE,
               "Si paso nombre valido se crea entrenador");
  entrenador_destruir(entrenador);
}
// Entrenador agregar pokemon
void DadoEntrenadorOAtributosDePokemonNULL_CuandoIntentoAgregarPokemonAEntrenador_EntoncesObtengoError() {
  entrenador_t *entrenador = entrenador_crear("entrenador1", 1);

  pa2m_afirmar(entrenador_insertar_pokemon(NULL, "Pokemon", 1, 1, 1, 1, 1) ==
                   ERROR,
               "No se puede agregar pokemon a entrenador null");
  pa2m_afirmar(entrenador_insertar_pokemon(entrenador, NULL, 1, 1, 1, 1, 1) ==
                   ERROR,
               "No se puede agregar pokemon con nombre null");
  entrenador_destruir(entrenador);
}

void DadoEntrenadorYAtributosDePokemonsValidos_CuandoAgregoPokemonAEntrenador_EntoncesCantidadDePokemonesAumenta() {
  entrenador_t *entrenador = entrenador_crear("entrenador1", 1);

  pa2m_afirmar(entrenador_insertar_pokemon(entrenador, "Pokemon", 1, 1, 1, 1,
                                           1) == EXITO,
               "Se pudo insertar pokemon");
  pa2m_afirmar(entrenador_cantidad_pokemones(entrenador) == 1,
               "Se incremento la cantidad de pokemones");
  pa2m_afirmar(entrenador_insertar_pokemon(entrenador, "Pokemon", 2, 2, 2, 2,
                                           2) == EXITO,
               "Si se inserta pokemon con mismo nombre se reescribe");
  pa2m_afirmar(entrenador_cantidad_pokemones(entrenador) == 1,
               "No se incremento la cantidad de pokemones");
  pa2m_afirmar(entrenador_insertar_pokemon(entrenador, "OtroPokemon", 1, 1, 1,
                                           1, 1) == EXITO,
               "Se pudo insertar pokemon");
  pa2m_afirmar(entrenador_cantidad_pokemones(entrenador) == 2,
               "Se incremento la cantidad de pokemones");
  entrenador_destruir(entrenador);
}

// Entrenador quitar pokemon
void DadoEntrenadorONombrePokemonInvalido_CuandoIntentoQuitarPokemon_EntoncesObtengoError() {
  entrenador_t *entrenador = entrenador_crear("entrenador1", 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon1", 1, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon2", 1, 1, 1, 1, 1);

  pa2m_afirmar(entrenador_quitar_pokemon(NULL, "Pokemon1") == ERROR,
               "No se puede quitar pokemon de entrenador null");

  pa2m_afirmar(
      entrenador_quitar_pokemon(entrenador, NULL) == ERROR,
      "Se debe pasar el nombre del pokemon que se busca quitar del entrenador");

  pa2m_afirmar(
      entrenador_quitar_pokemon(entrenador, "Este pokemon no existe") == ERROR,
      "No se puede quitar un pokemon que no existe");

  entrenador_destruir(entrenador);
}

void DadoEntrenadorONombrePokemonValidos_CuandoIntentoQuitarPokemonSiendoQueHayUnOMenosPokemonesEnEquipo_EntoncesObtengoError() {

  entrenador_t *entrenador = entrenador_crear("entrenador1", 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon", 1, 1, 1, 1, 1);

  pa2m_afirmar(entrenador_quitar_pokemon(entrenador, "Pokemon") == ERROR,
               "No se le puede quitar el ultimo pokemon a un entrenador");

  entrenador_destruir(entrenador);
}

void DadoEntrenadorONombrePokemonValidos_CuandoIntentoQuitarPokemon_EntoncesDisminuyeCantidadPokemones() {
  entrenador_t *entrenador = entrenador_crear("entrenador1", 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon1", 1, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon2", 1, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon3", 1, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon4", 1, 1, 1, 1, 1);

  pa2m_afirmar(entrenador_cantidad_pokemones(entrenador) == 4,
               "El entrenador posee 4 pokemones");
  pa2m_afirmar(entrenador_quitar_pokemon(entrenador, "Pokemon1") == EXITO,
               "Se pudo quitar el pokemon[1]");

  pa2m_afirmar(entrenador_cantidad_pokemones(entrenador) == 3,
               "El entrenador posee 3 pokemones");
  pa2m_afirmar(entrenador_quitar_pokemon(entrenador, "Pokemon2") == EXITO,
               "Se pudo quitar el pokemon[2]");

  pa2m_afirmar(entrenador_cantidad_pokemones(entrenador) == 2,
               "El entrenador posee 2 pokemones");
  pa2m_afirmar(entrenador_quitar_pokemon(entrenador, "Pokemon3") == EXITO,
               "Se pudo quitar el pokemon[3]");

  pa2m_afirmar(entrenador_cantidad_pokemones(entrenador) == 1,
               "El entrenador posee 1 pokemones");

  entrenador_destruir(entrenador);
}

// Entrenador buscar pokemon
void DadoEntrenadorONombrePokemonInvalidos_CuandoIntentoBuscarPokemon_EntoncesObtengoNULL() {
  entrenador_t *entrenador = entrenador_crear("Entrenador", 1);

  pa2m_afirmar(entrenador_buscar_pokemon(NULL, "pokemon") == NO_EXISTE,
               "No se puede buscar pokemon cuando no se recibe entrenador");
  pa2m_afirmar(entrenador_buscar_pokemon(entrenador, NULL) == NO_EXISTE,
               "Se debe pasar el nombre del pokemon para poder buscarlo");
  pa2m_afirmar(entrenador_buscar_pokemon(entrenador, "pokemon") == NO_EXISTE,
               "No existe pokemon buscado en entrenador vacio");

  entrenador_destruir(entrenador);
}

void DadoEntrenadorONombrePokemonValidos_CuandoIntentoBuscarPokemon_EntoncesObtengoElPokemonBuscado() {
  entrenador_t *entrenador = entrenador_crear("Entrenador", 1);

  entrenador_insertar_pokemon(entrenador, "Pokemon1", 1, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon2", 1, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon3", 1, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon4", 1, 1, 1, 1, 1);

  pa2m_afirmar(entrenador_buscar_pokemon(entrenador, "Pokemon1") != NO_EXISTE,
               "Se obtuvo en pokemon buscado[1]");
  pa2m_afirmar(entrenador_buscar_pokemon(entrenador, "Pokemon2") != NO_EXISTE,
               "Se obtuvo en pokemon buscado[2]");
  pa2m_afirmar(entrenador_buscar_pokemon(entrenador, "Pokemon3") != NO_EXISTE,
               "Se obtuvo en pokemon buscado[3]");
  pa2m_afirmar(entrenador_buscar_pokemon(entrenador, "Pokemon4") != NO_EXISTE,
               "Se obtuvo en pokemon buscado[4]");

  entrenador_destruir(entrenador);
}

// Entrenador comparador
void DadoEntrenadores_CuandoComparoEntrenadores_EntoncesObtengoElResultadoDeseado() {
  entrenador_t *entrenador1 = entrenador_crear("a", 1);
  entrenador_t *entrenador2 = entrenador_crear("b", 1);
  entrenador_t *entrenador3 = entrenador_crear("ba", 1);

  pa2m_afirmar(entrenador_comparador(entrenador1, entrenador2) < 0,
               "entrenador1 es menor a entrenador2");
  pa2m_afirmar(entrenador_comparador(entrenador1, entrenador1) == 0,
               "entrenador1 es igual a entrenador1");
  pa2m_afirmar(entrenador_comparador(entrenador3, entrenador2) > 0,
               "entrenador3 es mayor a entrenador2");

  entrenador_destruir(entrenador1);
  entrenador_destruir(entrenador2);
  entrenador_destruir(entrenador3);
}

// Entrenador Lista
void DadoEntrenadorNULL_CuandoIntentoObtenerLista_EntoncesObtengoNULL() {
  entrenador_t *entrenador = entrenador_crear("Entrenador", 1);

  lista_t *lista_pokemones1 = entrenador_lista_ordenada_pokemones(NULL, 0);
  pa2m_afirmar(lista_pokemones1 == NO_EXISTE,
               "Si no se pasa un entrendor se obtiene NULL");

  entrenador_destruir(entrenador);
}

void DadoEntrenadorYCantidad_CuandoIntentoObtenerLista_EntoncesObtengoListaConPokemones() {
  entrenador_t *entrenador = entrenador_crear("entrenador", 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon1", 3, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon2", 1, 3, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon3", 1, 1, 3, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon4", 1, 1, 1, 3, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon5", 1, 1, 4, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon6", 1, 4, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon7", 4, 1, 1, 1, 1);

  lista_t *lista_pokemones1 =
      entrenador_lista_ordenada_pokemones(entrenador, 0);
  size_t cantidad1 = lista_elementos(lista_pokemones1);
  pa2m_afirmar(cantidad1 == 7,
               "Se obtuvo una lista con la cantidad indicada[1]");

  lista_t *lista_pokemones2 =
      entrenador_lista_ordenada_pokemones(entrenador, 3);
  size_t cantidad2 = lista_elementos(lista_pokemones2);
  pa2m_afirmar(cantidad2 == 3,
               "Se obtuvo una lista con la cantidad indicada[2]");

  lista_t *lista_pokemones3 =
      entrenador_lista_ordenada_pokemones(entrenador, 0);
  size_t cantidad3 = lista_elementos(lista_pokemones3);
  pa2m_afirmar(cantidad3 == 7,
               "Se obtuvo una lista con la cantidad indicada[3]");

  lista_destruir(lista_pokemones1);
  lista_destruir(lista_pokemones2);
  lista_destruir(lista_pokemones3);

  entrenador_destruir(entrenador);
}

// Utils
// split
void DadoUnStringInvalido_CuandoIntentoSepararEnLista_EntoncesObtengoNULL() {
  pa2m_afirmar(split(NULL, ',') == NO_EXISTE,
               "Si se pasa un string null no se puede separar");
}

bool print_lista(void *elemento, void *contexto) {
  contexto = contexto;
  printf("%s\n", (char *)elemento);

  return true;
}

void DadoUnStringVacio_CuandoIntentoSepararEnLista_EntoncesObtengoListaConUnElemento() {
  lista_t *lista = split("", ',');
  pa2m_afirmar(lista_elementos(lista) == 1, "Lista vacia contiene un elemento");
  /* lista_con_cada_elemento(lista, print_lista, NULL); */
  destruir_lista_split(lista);
}

void DadoUnStringYSeparadorValidos_CuandoIntentoSepararEnLista_EntoncesObtengoListaConCantidadYElementosDeseados() {
  const char *string1 = "Probando,split";
  const char *string2 = "Probando;split";
  const char *string3 = "Probando split";
  const char *string4 = "Probando;;split";

  lista_t *lista1 = split(string1, ',');
  lista_t *lista2 = split(string2, ';');
  lista_t *lista3 = split(string3, ' ');
  lista_t *lista4 = split(string1, ' ');
  lista_t *lista5 = split(string4, ';');

  pa2m_afirmar(lista_elementos(lista1) == 2,
               "Lista tiene cantidad de elementos deseada[1]");
  /* lista_con_cada_elemento(lista1, print_lista, NULL); */
  pa2m_afirmar(lista_elementos(lista2) == 2,
               "Lista tiene cantidad de elementos deseada[2]");
  /* lista_con_cada_elemento(lista2, print_lista, NULL); */
  pa2m_afirmar(lista_elementos(lista3) == 2,
               "Lista tiene cantidad de elementos deseada[3]");
  /* lista_con_cada_elemento(lista3, print_lista, NULL); */
  pa2m_afirmar(lista_elementos(lista4) == 1,
               "Lista tiene cantidad de elementos deseada[4]");
  /* lista_con_cada_elemento(lista4, print_lista, NULL); */
  pa2m_afirmar(lista_elementos(lista5) == 3,
               "Lista tiene cantidad de elementos deseada[5]");
  /* lista_con_cada_elemento(lista5, print_lista, NULL); */

  destruir_lista_split(lista1);
  destruir_lista_split(lista2);
  destruir_lista_split(lista3);
  destruir_lista_split(lista4);
  destruir_lista_split(lista5);
}

// csv_reader
void DadoUnArchivoNULL_CuandoIntentoPasarArchivoALista_EntoncesObtengoNULL() {
  lista_t *lista_archivo_null = csv_reader(NULL, ',');
  pa2m_afirmar(lista_archivo_null == NO_EXISTE,
               "Si archivo es NULL se puede pasar a lista")
}

void DadoUnArchivo_CuandoPasoArchivoALista_EntoncesObtengoArchivoSeparadoPorLineasYSeparador() {
  FILE *archivo = fopen("archivos_pruebas/salon_pruebas1.csv", "r");

  if (!archivo) {
    pa2m_afirmar(0, "No se pudo abrir el archivo prueba");
    return;
  }

  lista_t *lista_salon = csv_reader(archivo, ';');

  pa2m_afirmar(lista_elementos(lista_salon) == 6,
               "Lista tiene cantidad de elementos deseada");
  lista_t *primer_linea = lista_elemento_en_posicion(lista_salon, 0);
  lista_t *segunda_linea = lista_elemento_en_posicion(lista_salon, 1);

  pa2m_afirmar(lista_elementos(primer_linea) == 2,
               "Lista primer linea contiene cantidad de elementos deseada");
  pa2m_afirmar(lista_elementos(segunda_linea) == 6,
               "Lista segunda linea contiene cantidad de elementos deseada");

  destruir_csv_lista(lista_salon);
  fclosen(archivo);
}

// Salon leer archivos
void DadoArchivoInexistenteONULL_CuandoIntentoLeerArchivo_EntoncesObtengoNULL() {
  salon_t *salon1 = salon_leer_archivo(NULL);
  pa2m_afirmar(salon1 == NO_EXISTE, "Si paso null como direccion obtengo null");
  salon_t *salon2 = salon_leer_archivo("Esta_direccion_no_existe");
  pa2m_afirmar(salon2 == NO_EXISTE,
               "Si paso una direccion inexistente obtengo null");
}

void DadoUnArchivoConSalonInvalido_CuandoIntentoLeerArchivo_EntoncesObtengoNULL() {
  salon_t *salon1 = salon_leer_archivo("archivos_pruebas/salon_vacio.csv");
  salon_t *salon2 =
      salon_leer_archivo("archivos_pruebas/salon_entrenador_sin_pokemones.csv");
  salon_t *salon3 = salon_leer_archivo("archivos_pruebas/salon_invalido1.csv");
  salon_t *salon4 = salon_leer_archivo("archivos_pruebas/salon_invalido2.csv");

  pa2m_afirmar(salon1 == NO_EXISTE,
               "Si paso un salon existente pero vacio obtengo error");
  pa2m_afirmar(salon2 == NO_EXISTE, "Si paso un salon existente pero hay "
                                    "entrenadores sin pokemones obtengo error");
  pa2m_afirmar(salon3 == NO_EXISTE, "Si paso un salon con formato invalido[1]");
  pa2m_afirmar(salon4 == NO_EXISTE, "Si paso un salon con formato invalido[2]");
}

void DadoUnArchivoExistente_CuandoIntentoLeerArchivo_EntoncesNoObtengoNULL() {
  salon_t *salon1 = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");
  pa2m_afirmar(salon1 != NO_EXISTE,
               "Si paso un salon, el salon se carga en memoria");

  salon_destruir(salon1);
}

// Salon guardar
void DadoUnSalonNULL_CuandoIntentoGuardarSalon_EntoncesObtengo0() {
  pa2m_afirmar(salon_guardar_archivo(
                   NULL, "archivos_pruebas/salon_guardar.csv") == ERROR,
               "Si el salon es NULL no se puede guardar");
}

void DadoUnSalonConEntrenadores_CuandoGuardoSalon_EntoncesObtengoCantidadDeEntrenadores() {
  // crea salon
  salon_t *salon = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");
  // guarda salon
  pa2m_afirmar(
      salon_guardar_archivo(salon, "archivos_pruebas/salon_guardar.csv") == 2,
      "Se guardo un archivo con la cantidad de entrenadores deseada");
  // crea salon con archivo guardado
  salon_t *salon_reabrir =
      salon_leer_archivo("archivos_pruebas/salon_guardar.csv");
  // guarda nuevamente
  int cantidad = salon_guardar_archivo(salon_reabrir,
                                       "archivos_pruebas/salon_guardar.csv");

  pa2m_afirmar(cantidad == 2,
               "El archivo guardado sigue conteniendo la cantidad deseada de "
               "entrenadores");
  // si la cantidad corresponde entonces guardar y salvar funcionan
  salon_destruir(salon);
  salon_destruir(salon_reabrir);
}

// Salon_agregar_entrenador
void DadoUnSalonOEntrenadorNullOInvalido_CuandoIntentoAgregarEntrenador_EntoncesObtengoNULL() {
  salon_t *salon = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");

  entrenador_t *entrenador = entrenador_crear("entrenador3", 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon1", 3, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon2", 1, 3, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon3", 1, 1, 3, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon4", 1, 1, 1, 3, 1);
  entrenador_t *entrenador_vacio = entrenador_crear("entrenador4", 1);
  entrenador_t *entrenador_repetido = entrenador_crear("entrenador1", 1);
  entrenador_insertar_pokemon(entrenador_repetido, "Pokemon1", 3, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador_repetido, "Pokemon2", 1, 3, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador_repetido, "Pokemon3", 1, 1, 3, 1, 1);
  entrenador_insertar_pokemon(entrenador_repetido, "Pokemon4", 1, 1, 1, 3, 1);

  pa2m_afirmar(salon_agregar_entrenador(NULL, entrenador) == NULL,
               "Si se pasa un salon null es imposible agregar entrenador");

  pa2m_afirmar(salon_agregar_entrenador(salon, NULL) == NULL,
               "Si se pasa un entrenador null es imposible agregar entrenador");

  pa2m_afirmar(
      salon_agregar_entrenador(salon, entrenador_vacio) == NULL,
      "El entrenador tiene que tener minimo un pokemon para entrar al salon");

  pa2m_afirmar(salon_agregar_entrenador(salon, entrenador_repetido) == NULL,
               "No se pude agregar un entrenador con mismo nombre");

  salon_destruir(salon);
  entrenador_destruir(entrenador);
  entrenador_destruir(entrenador_vacio);
  entrenador_destruir(entrenador_repetido);
}

void DadoUnSalonYEntrenador_CuandoAgregoEntrenador_EntoncesLaCantidadDeEntrenadoresIncrementa() {
  salon_t *salon = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");

  entrenador_t *entrenador = entrenador_crear("entrenador3", 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon1", 3, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon2", 1, 3, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon3", 1, 1, 3, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon4", 1, 1, 1, 3, 1);

  pa2m_afirmar(salon_agregar_entrenador(salon, entrenador) == salon,
               "Si paso un salon y un entrenador validos se grega");

  pa2m_afirmar(
      salon_guardar_archivo(salon, "archivos_pruebas/salon_guardar.csv") == 3,
      "Es salon contiene la cantidad de entrenadores deseada");

  salon_destruir(salon);
}

bool mas_de_35_victorias(entrenador_t *entrenador, void *extra) {
  if (!entrenador)
    return false;
  extra = extra;
  if (entrenador_victorias(entrenador) >= 35)
    return false;
  return true;
}

bool siempre_false(entrenador_t *entrenador, void *extra) {
  extra = extra;
  entrenador = entrenador;
  return false;
}
// TODO: verificar que en la documentacion se diga que con true el entrenador
// pasa y con false no
// Filtrar salon
void DadoUnSalonNULL_CuandoIntentoFiltrarSalon_EntoncesObtengoNULL() {
  pa2m_afirmar(salon_filtrar_entrenadores(NULL, mas_de_35_victorias, NULL) ==
                   NULL,
               "Si se pasa un salon null no se puede hacer filtrado");
}

void DadoUnSalonYFuncion_CuandoFiltroSalon_EntoncesObtengoListaConElementosDeseados() {
  salon_t *salon = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");
  lista_t *lista1 =
      salon_filtrar_entrenadores(salon, mas_de_35_victorias, NULL);
  lista_t *lista2 = salon_filtrar_entrenadores(salon, NULL, NULL);
  lista_t *lista3 = salon_filtrar_entrenadores(salon, siempre_false, NULL);
  size_t cantidad1 = lista_elementos(lista1);
  size_t cantidad2 = lista_elementos(lista2);
  size_t cantidad3 = lista_elementos(lista3);

  pa2m_afirmar(
      cantidad1 == 1,
      "Se obtiene la cantidad de entrenadores deseada despues del filtrado");
  pa2m_afirmar(
      cantidad2 == 2,
      "Si no se pasa funcion se devuelve una lista con todos los entrenadores");
  pa2m_afirmar(cantidad3 == 0, "Si no se encuentra ningun entrenador "
                               "compatible se devuelve una lista vacia");

  lista_destruir(lista1);
  lista_destruir(lista2);
  lista_destruir(lista3);
  salon_destruir(salon);
}

// Salon Ejecutar Comandos
void DadoUnSalonOComandoNULL_CuandoIntentoEjecutarComando_EntoncesObtengoNULL() {
  salon_t *salon = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");

  pa2m_afirmar(salon_ejecutar_comando(NULL, "ENTRENADORES") == NULL,
               "Si no se pasa un salon no se puede ejecutar comando");
  pa2m_afirmar(salon_ejecutar_comando(salon, NULL) == NULL,
               "Si no se pasa comando no se puede ejecutarlo");

  salon_destruir(salon);
}

void DadoUnSalonYComandoNoExistente_CuandoIntentoEjecutarComando_EntoncesObtengoNULL() {
  salon_t *salon = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");

  pa2m_afirmar(
      salon_ejecutar_comando(salon, "ESTE_COMANDO_NO_EXISTE:nada,nada") == NULL,
      "Si comando no existe no se puede ejecutar");

  salon_destruir(salon);
}

/* "ENTRENADORES" */
/* Respuesta :entrenador,victorias */
/* "ENTRENADORES:victorias,n" */
/* Respuesta : entrenador */
/* "ENTRENADORES:pokemon,nombre" */
/* Respuesta : entrenador */
void testear_commando_entrenador(salon_t *salon) {
  // Que pasa si pongo apenas entrenador
  char *resultado1 = salon_ejecutar_comando(salon, "ENTRENADORES");
  pa2m_afirmar(resultado1 &&
                   strcmp(resultado1, "entrenador1,33\nentrenador2,38\n") == 0,
               "El resultado obtenido al buscar entrenadores coincide [1]");
  char *resultado2 = salon_ejecutar_comando(salon, "ENTRENADORES:");
  pa2m_afirmar(resultado2 ==NULL,
               "Se paso un comando con formato incorrecto");
  // Que pasa si pongo entrenador y victorias
  char *resultado3 = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,35");
  pa2m_afirmar(
      resultado3 && strcmp(resultado3, "entrenador2,38\n") == 0,
      "El resultado obtenido al filtrar entrendor por victorias coincide [1]");
  char *resultado4 = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,33");
  pa2m_afirmar(
      resultado4 && strcmp(resultado4, "entrenador1,33\nentrenador2,38\n") == 0,
      "El resultado obtenido al filtrar entrendor por victorias coincide [2]");
  // Que pasa si las victorias no es un numero
  char *resultado5 = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,hola");
  pa2m_afirmar(resultado5  == NO_EXISTE,
               "Si no se pasa un numero al filtrar por victoria se devuelve "
               "string vacio");
  // Que pasa si no encuentra entrenador con cantidad de victorias
  char *resultado6 = salon_ejecutar_comando(salon, "ENTRENADORES:victorias,100");
  pa2m_afirmar(resultado6  == NO_EXISTE,
               "Si no se encuentra ningun entrenador al hacer filtrado de "
               "devuelve string vacio");
  // Que pasa si busco entrenador con pokemon
  char *resultado7 =
      salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,pokemon1");
  pa2m_afirmar(resultado7 && strcmp(resultado7, "entrenador1,33\n") == 0,
               "El resultado de un filtrado por pokemon coincide");
  // Que pasa si busco entrenador con pokemon y no paso nombre
  char *resultado8 = salon_ejecutar_comando(salon, "ENTRENADORES:pokemon");
  pa2m_afirmar(
      resultado8  == NO_EXISTE,
      "Si no se pasa nombre de pokemon entonces se devuelve un string vacio");
  // Que pasa si no encutra entrenador con pokemon
  char *resultado9 =
      salon_ejecutar_comando(salon, "ENTRENADORES:pokemon,pokemonNoExiste");
  pa2m_afirmar(resultado9 == NO_EXISTE,
               "Si no se encuentra entrenador con pokemon pasado se devuelve "
               "NULL");
}

/* "EQUIPO:nombre" */
/* Respuesta: nombre,nivel,defensa,fuerza,inteligencia,velocidad */
void testear_commando_equipo(salon_t *salon) {
  // Que pasa si encuentra entrenador con ese nombre
  // Que pasa si no encuentra entrenado con ese nombre
}

/* "REGLAS" */
/* Respuesta: nombre,descripción */
void testear_commando_reglas(salon_t *salon) {
  // Que pasa si podo este comando
}

/* "COMPARAR:entrenador1,entrenador2,nombreregla" */
/* Respuesta: 1 si gano el pokemon del primer entrenador 2 si gano el pokemon
 * del segundo entrenador */
void testear_commando_comparar(salon_t *salon) {
  // Que pasa si paso una regla inexistente
  // Que pasa si poso un entrenador inexistente
  // Que pasa si paso entrenadores validos y regla valida
}

/* "AGREGAR_POKEMON:nombre-entrenador,nombre-pokemon,nivel,defensa,fuerza,inteligencia,velocidad"
 */
/* Respuesta: OK */
void testear_commando_agregar_pokemon(salon_t *salon) {
  // Que pasa si paso entrenador invalido
  // Que pasa si los stats del pokemon no son numeros
  // Que pasa si poso entrenador y pokemon validos
}

/* "QUITAR_POKEMON:nombre-entrenador,nombre-pokemon" */
/* Respuesta: OK */
void testear_commando_quitar_pokemon(salon_t *salon) {
  // Que pasa si paso entrenador invalido
  // Que pasa si paso pokemon invalido
  // Que pasa si paso entrenador y pokemon validos
}

/* "GUARDAR:nombre-archivo" */
/* Respuesta: OK */
void testear_commando_guardar(salon_t *salon) {
  // Que pasa llamo comando
}

void DadoUnSalonYComandoValido_CuandoIntentoEjecutarComando_EntonceObtengoCharDeseado() {
  salon_t *salon = salon_leer_archivo("archivos_pruebas/salon_pruebas1.csv");

  pa2m_nuevo_grupo("ENTRENADOR");
  testear_commando_entrenador(salon);

  pa2m_nuevo_grupo("EQUIPO");
  testear_commando_equipo(salon);

  pa2m_nuevo_grupo("REGLAS");
  testear_commando_reglas(salon);

  pa2m_nuevo_grupo("COMPARAR");
  testear_commando_comparar(salon);

  pa2m_nuevo_grupo("AGREGAR_POKEMON");
  testear_commando_agregar_pokemon(salon);

  pa2m_nuevo_grupo("QUITAR_POKEMON");
  testear_commando_quitar_pokemon(salon);

  pa2m_nuevo_grupo("GUARDAR");
  testear_commando_guardar(salon);

  salon_destruir(salon);
}

int main() {
  pa2m_nuevo_grupo("Entrenador Crear");
  DadoNombreNULL_CuandoIntentoCrearEntrenador_EntoncesObtengoNULL();
  DadoNombreValido_CuandoCreoEntrenador_EntoncesNoObtengoNULL();
  pa2m_nuevo_grupo("Entrenador Agregar");
  DadoEntrenadorOAtributosDePokemonNULL_CuandoIntentoAgregarPokemonAEntrenador_EntoncesObtengoError();
  DadoEntrenadorYAtributosDePokemonsValidos_CuandoAgregoPokemonAEntrenador_EntoncesCantidadDePokemonesAumenta();
  pa2m_nuevo_grupo("Entrenador Quitar");
  DadoEntrenadorONombrePokemonInvalido_CuandoIntentoQuitarPokemon_EntoncesObtengoError();
  DadoEntrenadorONombrePokemonValidos_CuandoIntentoQuitarPokemonSiendoQueHayUnOMenosPokemonesEnEquipo_EntoncesObtengoError();
  DadoEntrenadorONombrePokemonValidos_CuandoIntentoQuitarPokemon_EntoncesDisminuyeCantidadPokemones();
  pa2m_nuevo_grupo("Entrenador Buscar");
  DadoEntrenadorONombrePokemonInvalidos_CuandoIntentoBuscarPokemon_EntoncesObtengoNULL();
  DadoEntrenadorONombrePokemonValidos_CuandoIntentoBuscarPokemon_EntoncesObtengoElPokemonBuscado();
  pa2m_nuevo_grupo("Entrenador Comparar");
  DadoEntrenadores_CuandoComparoEntrenadores_EntoncesObtengoElResultadoDeseado();
  pa2m_nuevo_grupo("Entrenador Listar");
  DadoEntrenadorNULL_CuandoIntentoObtenerLista_EntoncesObtengoNULL();
  DadoEntrenadorYCantidad_CuandoIntentoObtenerLista_EntoncesObtengoListaConPokemones();

  pa2m_nuevo_grupo("Utils");
  DadoUnStringInvalido_CuandoIntentoSepararEnLista_EntoncesObtengoNULL();
  DadoUnStringVacio_CuandoIntentoSepararEnLista_EntoncesObtengoListaConUnElemento();
  DadoUnStringYSeparadorValidos_CuandoIntentoSepararEnLista_EntoncesObtengoListaConCantidadYElementosDeseados();
  DadoUnArchivoNULL_CuandoIntentoPasarArchivoALista_EntoncesObtengoNULL();
  DadoUnArchivo_CuandoPasoArchivoALista_EntoncesObtengoArchivoSeparadoPorLineasYSeparador();

  pa2m_nuevo_grupo("Salon leer archivo");
  DadoArchivoInexistenteONULL_CuandoIntentoLeerArchivo_EntoncesObtengoNULL();
  DadoUnArchivoConSalonInvalido_CuandoIntentoLeerArchivo_EntoncesObtengoNULL();
  DadoUnArchivoExistente_CuandoIntentoLeerArchivo_EntoncesNoObtengoNULL();

  pa2m_nuevo_grupo("Salon guardar archivo");
  DadoUnSalonNULL_CuandoIntentoGuardarSalon_EntoncesObtengo0();
  DadoUnSalonConEntrenadores_CuandoGuardoSalon_EntoncesObtengoCantidadDeEntrenadores();

  pa2m_nuevo_grupo("Salon agregar entrenador");
  DadoUnSalonOEntrenadorNullOInvalido_CuandoIntentoAgregarEntrenador_EntoncesObtengoNULL();
  DadoUnSalonYEntrenador_CuandoAgregoEntrenador_EntoncesLaCantidadDeEntrenadoresIncrementa();

  pa2m_nuevo_grupo("Filtrar salon");
  DadoUnSalonNULL_CuandoIntentoFiltrarSalon_EntoncesObtengoNULL();
  DadoUnSalonYFuncion_CuandoFiltroSalon_EntoncesObtengoListaConElementosDeseados();

  pa2m_nuevo_grupo("Salon ejecutar comandos");
  DadoUnSalonOComandoNULL_CuandoIntentoEjecutarComando_EntoncesObtengoNULL();
  DadoUnSalonYComandoNoExistente_CuandoIntentoEjecutarComando_EntoncesObtengoNULL();
  DadoUnSalonYComandoValido_CuandoIntentoEjecutarComando_EntonceObtengoCharDeseado();

  return pa2m_mostrar_reporte();
}
