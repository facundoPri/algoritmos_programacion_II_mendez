#include "pa2mm.h"
#include "src/lista.h"
#include "src/salon.h"
#include "tdas/tp1_salon_de_la_fama/pa2mm.h"

#define NO_EXISTE NULL

// Salon leer archivos
void DadoArchivoInexistenteONULL_CuandoIntentoLeerArchivo_EntoncesObtengoNULL() {
  salon_t *salon1 = salon_leer_archivo(NULL);
  pa2m_afirmar(salon1 == NO_EXISTE, "Si paso null como direccion obtengo null");
  salon_t *salon2 = salon_leer_archivo("Esta_direccion_no_existe");
  pa2m_afirmar(salon2 == NO_EXISTE,
               "Si paso una direccion inexistente obtengo null");
}

void DadoUnArchivoExistente_CuandoIntentoLeerArchivo_EntoncesNoObtengoNULL() {
  salon_t *salon1 = salon_leer_archivo("archivos_pruebas/salon_vacio.csv");
  pa2m_afirmar(
      salon1 != NO_EXISTE,
      "Si paso un salon existente pero vacio igual se carga un salon vacio");
  salon_t *salon2 = salon_leer_archivo("archivos_prubas/salon_prueba1.csv");
  pa2m_afirmar(salon2 == NO_EXISTE,
               "Si paso un salon, el salon se carga en memoria");

  salon_destruir(salon1);
  salon_destruir(salon2);
}

// TODO: Solo se puede cargar entrenador con minimo 1 pokemon

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

  pa2m_nuevo_grupo("Salon leer archivo");
  DadoArchivoInexistenteONULL_CuandoIntentoLeerArchivo_EntoncesObtengoNULL();
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
