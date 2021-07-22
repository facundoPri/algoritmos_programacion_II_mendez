#include "pa2mm.h"
#include "src/lista.h"
#include "src/salon.h"
#include <stdio.h>

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

  pa2m_afirmar(entrenador_comparador(entrenador1, entrenador2) > 0,
               "entrenador1 es menor a entrenador2");
  pa2m_afirmar(entrenador_comparador(entrenador1, entrenador1) == 0,
               "entrenador1 es igual a entrenador1");
  pa2m_afirmar(entrenador_comparador(entrenador3, entrenador2) < 0,
               "entrenador3 es mayor a entrenador2");

  entrenador_destruir(entrenador1);
  entrenador_destruir(entrenador2);
  entrenador_destruir(entrenador3);
}

// Entrenador Lista
void DadoEntrenadorOMetodoNULL_CuandoIntentoObtenerLista_EntoncesObtengoNULL() {
  entrenador_t *entrenador = entrenador_crear("Entrenador", 1);

  lista_t *lista_pokemones1 =
      entrenador_lista_ordenada_pokemones(NULL, METODO_CLASICO, 0);
  lista_t *lista_pokemones2 =
      entrenador_lista_ordenada_pokemones(entrenador, 0, 0);
  pa2m_afirmar(lista_pokemones1 == NO_EXISTE,
               "Si no se pasa un entrendor se obtiene NULL");
  pa2m_afirmar(lista_pokemones2 == NO_EXISTE,
               "Si no se pasa metodo de batalla se obtiene NULL");

  entrenador_destruir(entrenador);
}

void DadoEntrenadorMetodoYCantidad_CuandoIntentoObtenerLista_EntoncesObtengoListaConPokemones() {
  entrenador_t *entrenador = entrenador_crear("entrenador", 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon1", 3, 1, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon2", 1, 3, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon3", 1, 1, 3, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon4", 1, 1, 1, 3, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon5", 1, 1, 4, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon6", 1, 4, 1, 1, 1);
  entrenador_insertar_pokemon(entrenador, "Pokemon7", 4, 1, 1, 1, 1);

  lista_t *lista_pokemones1 =
      entrenador_lista_ordenada_pokemones(entrenador, METODO_CLASICO, 0);
  size_t cantidad1 = lista_con_cada_elemento(lista_pokemones1, NULL, NULL);
  pa2m_afirmar(cantidad1 == 7,
               "Se obtuvo una lista con la cantidad indicada[1]");

  lista_t *lista_pokemones2 =
      entrenador_lista_ordenada_pokemones(entrenador, METODO_CLASICO, 3);
  size_t cantidad2 = lista_con_cada_elemento(lista_pokemones2, NULL, NULL);
  pa2m_afirmar(cantidad2 == 3,
               "Se obtuvo una lista con la cantidad indicada[2]");

  lista_t *lista_pokemones3 =
      entrenador_lista_ordenada_pokemones(entrenador, METODO_MODERNO, 0);
  size_t cantidad3 = lista_con_cada_elemento(lista_pokemones3, NULL, NULL);
  pa2m_afirmar(cantidad3 == 7,
               "Se obtuvo una lista con la cantidad indicada[3]");

  lista_destruir(lista_pokemones1);
  lista_destruir(lista_pokemones2);
  lista_destruir(lista_pokemones3);

  entrenador_destruir(entrenador);
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
  salon_t *salon1 = salon_leer_archivo("archivos_prubas/salon_prueba1.csv");
  pa2m_afirmar(salon1 != NO_EXISTE,
               "Si paso un salon, el salon se carga en memoria");

  salon_destruir(salon1);
}

// Salon guardar
void DadoUnSalonNULL_CuandoIntentoGuardarSalon_EntoncesObtengo0() {}

void DadoUnSalonConEntrenadores_CuandoGuardoSalon_EntoncesObtengoCantidadDeEntrenadores() {
  // crea salon
  // guarda salon
  // crea salon con archivo guardado
  // guarda nuevamente
  // si la cantidad corresponde entonces guardar y salvar funcionan
}

// Salon_agregar_entrenador
void DadoUnSalonOEntrenadorNull_CuandoIntentoAgregarEntrenador_EntoncesObtengoNULL() {

}

void DadoUnSalonYEntrenador_CuandoAgregoEntrenador_EntoncesLaCantidadDeEntrenadoresIncrementa() {

}

// Filtrar salon
void DadoUnSalonOFuncionNULL_CuandoIntentoFiltrarSalon_EntoncesObtengoNULL() {}

void DadoUnSalonYFuncion_CuandoFiltroSalon_EntoncesObtengoListaConElementosDeseados() {

}

// Salon Ejecutar Comandos
void DadoUnSalonOComandoNULL_CuandoIntentoEjecutarComando_EntoncesObtengoNULL() {

}

void DadoUnSalonYComandoNoExistente_CuandoIntentoEjecutarComando_EntoncesObtengoNULL() {

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
  DadoEntrenadorOMetodoNULL_CuandoIntentoObtenerLista_EntoncesObtengoNULL();
  DadoEntrenadorMetodoYCantidad_CuandoIntentoObtenerLista_EntoncesObtengoListaConPokemones();

  pa2m_nuevo_grupo("Salon leer archivo");
  DadoArchivoInexistenteONULL_CuandoIntentoLeerArchivo_EntoncesObtengoNULL();
  DadoUnArchivoConSalonInvalido_CuandoIntentoLeerArchivo_EntoncesObtengoNULL();
  DadoUnArchivoExistente_CuandoIntentoLeerArchivo_EntoncesNoObtengoNULL();

  pa2m_nuevo_grupo("Salon guardar archivo");
  DadoUnSalonNULL_CuandoIntentoGuardarSalon_EntoncesObtengo0();
  DadoUnSalonConEntrenadores_CuandoGuardoSalon_EntoncesObtengoCantidadDeEntrenadores();

  pa2m_nuevo_grupo("Salon agregar entrenador");
  DadoUnSalonOEntrenadorNull_CuandoIntentoAgregarEntrenador_EntoncesObtengoNULL();
  DadoUnSalonOEntrenadorNull_CuandoIntentoAgregarEntrenador_EntoncesObtengoNULL();

  pa2m_nuevo_grupo("Filtrar salon");
  DadoUnSalonOFuncionNULL_CuandoIntentoFiltrarSalon_EntoncesObtengoNULL();
  DadoUnSalonYFuncion_CuandoFiltroSalon_EntoncesObtengoListaConElementosDeseados();

  pa2m_nuevo_grupo("Salon ejecutar comandos");
  DadoUnSalonOComandoNULL_CuandoIntentoEjecutarComando_EntoncesObtengoNULL();
  DadoUnSalonYComandoNoExistente_CuandoIntentoEjecutarComando_EntoncesObtengoNULL();

  return pa2m_mostrar_reporte();
}
