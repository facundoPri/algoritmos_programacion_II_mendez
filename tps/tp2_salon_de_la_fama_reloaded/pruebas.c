#include "pa2mm.h"
#include "src/lista.h"
#include "src/salon.h"

// Salon leer archivos
void DadoArchivoInexistente_CuandoIntentoLeerArchivo_EntoncesObtengoNULL() {}

void DadoUnArchivoExistente_CuandoIntentoLeerArchivo_EntoncesNoObtengoNULL() {}

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

  pa2m_nuevo_grupo("Alguna prueba");

  return pa2m_mostrar_reporte();
}
